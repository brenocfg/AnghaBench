#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
struct utsname {char* nodename; char* sysname; char* release; } ;
struct TYPE_4__ {size_t len; scalar_t__* subs; } ;
struct TYPE_3__ {TYPE_2__ object_id; int /*<<< orphan*/ * descr; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 size_t ASN_MAXOIDLEN ; 
 int /*<<< orphan*/  KERN_HOSTID ; 
 char* act_getkernint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 TYPE_2__ oid_freeBSDVersion ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ strtoul (char*,char**,int) ; 
 TYPE_1__ systemg ; 
 int uname (struct utsname*) ; 

int
init_actvals(void)
{
	struct utsname uts;
	char *hostid;
	size_t len;
#ifdef __FreeBSD__
	char *rel, *p, *end;
	u_long num;
#endif

	if (uname(&uts) == -1)
		return (-1);

	if ((systemg.name = strdup(uts.nodename)) == NULL)
		return (-1);

	if ((hostid = act_getkernint(KERN_HOSTID)) == NULL)
		return (-1);

	len = strlen(uts.nodename) + 1;
	len += strlen(hostid) + 1;
	len += strlen(uts.sysname) + 1;
	len += strlen(uts.release) + 1;

	if ((systemg.descr = malloc(len)) == NULL) {
		free(hostid);
		return (-1);
	}
	sprintf(systemg.descr, "%s %s %s %s", uts.nodename, hostid, uts.sysname,
	    uts.release);

#ifdef __FreeBSD__
	/*
	 * Construct a FreeBSD oid
	 */
	systemg.object_id = oid_freeBSDVersion;
	rel = uts.release;
	while ((p = strsep(&rel, ".")) != NULL &&
	    systemg.object_id.len < ASN_MAXOIDLEN) {
		systemg.object_id.subs[systemg.object_id.len] = 0;
		if (*p != '\0') {
			num = strtoul(p, &end, 10);
			if (end == p)
				break;
			systemg.object_id.subs[systemg.object_id.len] = num;
		}
		systemg.object_id.len++;
	}
#endif

	free(hostid);

	return (0);
}