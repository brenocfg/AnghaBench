#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uid_t ;
struct devfs_vnode_event {int dummy; } ;
struct devfs_event_log {int dummy; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_15__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_3__ devnode_type_t ;
struct TYPE_13__ {int /*<<< orphan*/  myname; } ;
struct TYPE_14__ {TYPE_1__ Dir; } ;
struct TYPE_16__ {TYPE_2__ dn_typeinfo; } ;
typedef  TYPE_4__ devnode_t ;
typedef  int /*<<< orphan*/  devfstype_t ;
struct TYPE_17__ {TYPE_6__* de_dnp; } ;
typedef  TYPE_5__ devdirent_t ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_18__ {int dn_mode; int (* dn_clone ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  dn_uid; int /*<<< orphan*/  dn_gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFS_CREATE ; 
 int /*<<< orphan*/  DEVFS_LOCK () ; 
 int /*<<< orphan*/  DEVFS_UNLOCK () ; 
 int NUM_STACK_ENTRIES ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 scalar_t__ dev_add_entry (char*,TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__**) ; 
 scalar_t__ dev_finddir (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__**,struct devfs_event_log*) ; 
 int /*<<< orphan*/  devfs_bulk_notify (struct devfs_event_log*) ; 
 scalar_t__ devfs_init_event_log (struct devfs_event_log*,int,struct devfs_vnode_event*) ; 
 int devfs_nmountplanes ; 
 int /*<<< orphan*/  devfs_propogate (int /*<<< orphan*/ ,TYPE_5__*,struct devfs_event_log*) ; 
 int /*<<< orphan*/  devfs_ready ; 
 int /*<<< orphan*/  devfs_release_event_log (struct devfs_event_log*,int) ; 
 int /*<<< orphan*/  mac_devfs_label_associate_device (int /*<<< orphan*/ ,TYPE_6__*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static devdirent_t *
devfs_make_node_internal(dev_t dev, devfstype_t type, uid_t uid, 
		gid_t gid, int perms, int (*clone)(dev_t dev, int action), const char *fmt, va_list ap)
{
	devdirent_t *	new_dev = NULL;
	devnode_t * dnp;
	devnode_type_t	typeinfo;

	char 		*name, buf[256]; /* XXX */
	const char 	*path;
#if CONFIG_MACF
	char buff[sizeof(buf)];
#endif
	int 		i;
	uint32_t 	log_count;
	struct devfs_event_log event_log;
	struct devfs_vnode_event stackbuf[NUM_STACK_ENTRIES];
	int		need_free = 0;

	vsnprintf(buf, sizeof(buf), fmt, ap);

#if CONFIG_MACF
	bcopy(buf, buff, sizeof(buff));
	buff[sizeof(buff)-1] = 0;
#endif
	name = NULL;

	for(i=strlen(buf); i>0; i--)
		if(buf[i] == '/') {
			name=&buf[i];
			buf[i]=0;
			break;
		}

	if (name) {
		*name++ = '\0';
		path = buf;
	} else {
		name = buf;
		path = "/";
	}

	log_count = devfs_nmountplanes;
	if (log_count > NUM_STACK_ENTRIES) {
wrongsize:
		need_free = 1;
		if (devfs_init_event_log(&event_log, log_count, NULL) != 0) {
			return NULL;
		}
	} else {
		need_free = 0;
		log_count = NUM_STACK_ENTRIES;
		if (devfs_init_event_log(&event_log, log_count, &stackbuf[0]) != 0) {
			return NULL;
		}
	}

	DEVFS_LOCK();
	if (log_count < devfs_nmountplanes) {
		DEVFS_UNLOCK();
		devfs_release_event_log(&event_log, need_free);
		log_count = log_count * 2;
		goto wrongsize;
	}
	
	if (!devfs_ready) {
		printf("devfs_make_node: not ready for devices!\n");
		goto out;
	}

	/* find/create directory path ie. mkdir -p */
	if (dev_finddir(path, NULL, DEVFS_CREATE, &dnp, &event_log) == 0) {
	    typeinfo.dev = dev;
	    if (dev_add_entry(name, dnp, type, &typeinfo, NULL, NULL, &new_dev) == 0) {
		new_dev->de_dnp->dn_gid = gid;
		new_dev->de_dnp->dn_uid = uid;
		new_dev->de_dnp->dn_mode |= perms;
		new_dev->de_dnp->dn_clone = clone;
#if CONFIG_MACF
		mac_devfs_label_associate_device(dev, new_dev->de_dnp, buff);
#endif
		devfs_propogate(dnp->dn_typeinfo.Dir.myname, new_dev, &event_log);
	    }
	}

out:
	DEVFS_UNLOCK();

	devfs_bulk_notify(&event_log);
	devfs_release_event_log(&event_log, need_free);
	return new_dev;
}