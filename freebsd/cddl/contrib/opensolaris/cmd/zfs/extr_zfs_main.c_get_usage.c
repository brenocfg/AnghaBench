#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int zfs_help_t ;

/* Variables and functions */
#define  HELP_ALLOW 158 
#define  HELP_BOOKMARK 157 
#define  HELP_CHANNEL_PROGRAM 156 
#define  HELP_CLONE 155 
#define  HELP_CREATE 154 
#define  HELP_DESTROY 153 
#define  HELP_DIFF 152 
#define  HELP_GET 151 
#define  HELP_GROUPSPACE 150 
#define  HELP_HOLD 149 
#define  HELP_HOLDS 148 
#define  HELP_INHERIT 147 
#define  HELP_JAIL 146 
#define  HELP_LIST 145 
#define  HELP_MOUNT 144 
#define  HELP_PROMOTE 143 
#define  HELP_RECEIVE 142 
#define  HELP_RELEASE 141 
#define  HELP_REMAP 140 
#define  HELP_RENAME 139 
#define  HELP_ROLLBACK 138 
#define  HELP_SEND 137 
#define  HELP_SET 136 
#define  HELP_SHARE 135 
#define  HELP_SNAPSHOT 134 
#define  HELP_UNALLOW 133 
#define  HELP_UNJAIL 132 
#define  HELP_UNMOUNT 131 
#define  HELP_UNSHARE 130 
#define  HELP_UPGRADE 129 
#define  HELP_USERSPACE 128 
 int /*<<< orphan*/  abort () ; 
 char const* gettext (char*) ; 

__attribute__((used)) static const char *
get_usage(zfs_help_t idx)
{
	switch (idx) {
	case HELP_CLONE:
		return (gettext("\tclone [-p] [-o property=value] ... "
		    "<snapshot> <filesystem|volume>\n"));
	case HELP_CREATE:
		return (gettext("\tcreate [-pu] [-o property=value] ... "
		    "<filesystem>\n"
		    "\tcreate [-ps] [-b blocksize] [-o property=value] ... "
		    "-V <size> <volume>\n"));
	case HELP_DESTROY:
		return (gettext("\tdestroy [-fnpRrv] <filesystem|volume>\n"
		    "\tdestroy [-dnpRrv] "
		    "<filesystem|volume>@<snap>[%<snap>][,...]\n"
		    "\tdestroy <filesystem|volume>#<bookmark>\n"));
	case HELP_GET:
		return (gettext("\tget [-rHp] [-d max] "
		    "[-o \"all\" | field[,...]]\n"
		    "\t    [-t type[,...]] [-s source[,...]]\n"
		    "\t    <\"all\" | property[,...]> "
		    "[filesystem|volume|snapshot|bookmark] ...\n"));
	case HELP_INHERIT:
		return (gettext("\tinherit [-rS] <property> "
		    "<filesystem|volume|snapshot> ...\n"));
	case HELP_UPGRADE:
		return (gettext("\tupgrade [-v]\n"
		    "\tupgrade [-r] [-V version] <-a | filesystem ...>\n"));
	case HELP_JAIL:
		return (gettext("\tjail <jailid|jailname> <filesystem>\n"));
	case HELP_UNJAIL:
		return (gettext("\tunjail <jailid|jailname> <filesystem>\n"));
	case HELP_LIST:
		return (gettext("\tlist [-Hp] [-r|-d max] [-o property[,...]] "
		    "[-s property]...\n\t    [-S property]... [-t type[,...]] "
		    "[filesystem|volume|snapshot] ...\n"));
	case HELP_MOUNT:
		return (gettext("\tmount\n"
		    "\tmount [-vO] [-o opts] <-a | filesystem>\n"));
	case HELP_PROMOTE:
		return (gettext("\tpromote <clone-filesystem>\n"));
	case HELP_RECEIVE:
		return (gettext("\treceive|recv [-vnsFu] <filesystem|volume|"
		    "snapshot>\n"
		    "\treceive|recv [-vnsFu] [-o origin=<snapshot>] [-d | -e] "
		    "<filesystem>\n"
		    "\treceive|recv -A <filesystem|volume>\n"));
	case HELP_RENAME:
		return (gettext("\trename [-f] <filesystem|volume|snapshot> "
		    "<filesystem|volume|snapshot>\n"
		    "\trename [-f] -p <filesystem|volume> <filesystem|volume>\n"
		    "\trename -r <snapshot> <snapshot>\n"
		    "\trename <bookmark> <bookmark>\n"
		    "\trename -u [-p] <filesystem> <filesystem>"));
	case HELP_ROLLBACK:
		return (gettext("\trollback [-rRf] <snapshot>\n"));
	case HELP_SEND:
		return (gettext("\tsend [-DnPpRvLec] [-[iI] snapshot] "
		    "<snapshot>\n"
		    "\tsend [-LPcenv] [-i snapshot|bookmark] "
		    "<filesystem|volume|snapshot>\n"
		    "\tsend [-nvPe] -t <receive_resume_token>\n"));
	case HELP_SET:
		return (gettext("\tset <property=value> ... "
		    "<filesystem|volume|snapshot> ...\n"));
	case HELP_SHARE:
		return (gettext("\tshare <-a | filesystem>\n"));
	case HELP_SNAPSHOT:
		return (gettext("\tsnapshot|snap [-r] [-o property=value] ... "
		    "<filesystem|volume>@<snap> ...\n"));
	case HELP_UNMOUNT:
		return (gettext("\tunmount|umount [-f] "
		    "<-a | filesystem|mountpoint>\n"));
	case HELP_UNSHARE:
		return (gettext("\tunshare "
		    "<-a | filesystem|mountpoint>\n"));
	case HELP_ALLOW:
		return (gettext("\tallow <filesystem|volume>\n"
		    "\tallow [-ldug] "
		    "<\"everyone\"|user|group>[,...] <perm|@setname>[,...]\n"
		    "\t    <filesystem|volume>\n"
		    "\tallow [-ld] -e <perm|@setname>[,...] "
		    "<filesystem|volume>\n"
		    "\tallow -c <perm|@setname>[,...] <filesystem|volume>\n"
		    "\tallow -s @setname <perm|@setname>[,...] "
		    "<filesystem|volume>\n"));
	case HELP_UNALLOW:
		return (gettext("\tunallow [-rldug] "
		    "<\"everyone\"|user|group>[,...]\n"
		    "\t    [<perm|@setname>[,...]] <filesystem|volume>\n"
		    "\tunallow [-rld] -e [<perm|@setname>[,...]] "
		    "<filesystem|volume>\n"
		    "\tunallow [-r] -c [<perm|@setname>[,...]] "
		    "<filesystem|volume>\n"
		    "\tunallow [-r] -s @setname [<perm|@setname>[,...]] "
		    "<filesystem|volume>\n"));
	case HELP_USERSPACE:
		return (gettext("\tuserspace [-Hinp] [-o field[,...]] "
		    "[-s field] ...\n"
		    "\t    [-S field] ... [-t type[,...]] "
		    "<filesystem|snapshot>\n"));
	case HELP_GROUPSPACE:
		return (gettext("\tgroupspace [-Hinp] [-o field[,...]] "
		    "[-s field] ...\n"
		    "\t    [-S field] ... [-t type[,...]] "
		    "<filesystem|snapshot>\n"));
	case HELP_HOLD:
		return (gettext("\thold [-r] <tag> <snapshot> ...\n"));
	case HELP_HOLDS:
		return (gettext("\tholds [-Hp] [-r|-d depth] "
		    "<filesystem|volume|snapshot> ...\n"));
	case HELP_RELEASE:
		return (gettext("\trelease [-r] <tag> <snapshot> ...\n"));
	case HELP_DIFF:
		return (gettext("\tdiff [-FHt] <snapshot> "
		    "[snapshot|filesystem]\n"));
	case HELP_REMAP:
		return (gettext("\tremap <filesystem | volume>\n"));
	case HELP_BOOKMARK:
		return (gettext("\tbookmark <snapshot> <bookmark>\n"));
	case HELP_CHANNEL_PROGRAM:
		return (gettext("\tprogram [-jn] [-t <instruction limit>] "
		    "[-m <memory limit (b)>] <pool> <program file> "
		    "[lua args...]\n"));
	}

	abort();
	/* NOTREACHED */
}