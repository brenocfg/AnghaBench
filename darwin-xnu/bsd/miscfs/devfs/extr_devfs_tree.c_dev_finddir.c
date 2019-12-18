#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_6__* myname; } ;
struct TYPE_16__ {TYPE_1__ Dir; } ;
struct TYPE_17__ {scalar_t__ dn_type; TYPE_2__ dn_typeinfo; } ;
typedef  TYPE_3__ devnode_t ;
typedef  int /*<<< orphan*/  devfs_event_log_t ;
struct TYPE_18__ {TYPE_3__* de_dnp; } ;
typedef  TYPE_4__ devdirent_t ;
struct TYPE_20__ {TYPE_3__* de_dnp; } ;
struct TYPE_19__ {char const* de_name; } ;

/* Variables and functions */
 int DEVMAXPATHSIZE ; 
 scalar_t__ DEV_DIR ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int dev_add_entry (char*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__**) ; 
 TYPE_4__* dev_findname (TYPE_3__*,char*) ; 
 TYPE_8__* dev_root ; 
 int /*<<< orphan*/  devfs_propogate (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_devfs_label_associate_directory (char const*,int,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
dev_finddir(const char * path, 
	    devnode_t * dirnode,
	    int create, 
	    devnode_t * * dn_pp,
	    devfs_event_log_t delp)
{
	devnode_t *	dnp = NULL;
	int		error = 0;
	const char *		scan;
#if CONFIG_MACF
	char            fullpath[DEVMAXPATHSIZE];
#endif


	if (!dirnode) /* dirnode == NULL means start at root */
	    dirnode = dev_root->de_dnp;

	if (dirnode->dn_type != DEV_DIR) 
	    return ENOTDIR;

	if (strlen(path) > (DEVMAXPATHSIZE - 1)) 
	    return ENAMETOOLONG;

#if CONFIG_MACF
	strlcpy (fullpath, path, DEVMAXPATHSIZE);
#endif
	scan = path;

	while (*scan == '/') 
	    scan++;

	*dn_pp = NULL;

	while (1) {
	    char		component[DEVMAXPATHSIZE];
	    devdirent_t *	dirent_p;
	    const char * 	start;

	    if (*scan == 0) { 
		/* we hit the end of the string, we're done */
		*dn_pp = dirnode;
		break;
	    }
	    start = scan;
	    while (*scan != '/' && *scan)
		scan++;

	    strlcpy(component, start, (scan - start) + 1);
	    if (*scan == '/')
		scan++;

	    dirent_p = dev_findname(dirnode, component);
	    if (dirent_p) {
		dnp = dirent_p->de_dnp;
		if (dnp->dn_type != DEV_DIR) {
		    error = ENOTDIR;
		    break;
		}
	    }
	    else {
		if (!create) {
		    error = ENOENT;
		    break;
		}
		error = dev_add_entry(component, dirnode, 
				       DEV_DIR, NULL, NULL, NULL, &dirent_p);
		if (error)
		    break;
		dnp = dirent_p->de_dnp;
#if CONFIG_MACF
		mac_devfs_label_associate_directory(
		    dirnode->dn_typeinfo.Dir.myname->de_name, 
		    strlen(dirnode->dn_typeinfo.Dir.myname->de_name),
		    dnp, fullpath);
#endif
		devfs_propogate(dirnode->dn_typeinfo.Dir.myname, dirent_p, delp);
	    }
	    dirnode = dnp; /* continue relative to this directory */
	}
	return (error);
}