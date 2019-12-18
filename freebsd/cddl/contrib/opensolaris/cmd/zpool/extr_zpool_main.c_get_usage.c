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
typedef  int zpool_help_t ;

/* Variables and functions */
#define  HELP_ADD 154 
#define  HELP_ATTACH 153 
#define  HELP_CHECKPOINT 152 
#define  HELP_CLEAR 151 
#define  HELP_CREATE 150 
#define  HELP_DESTROY 149 
#define  HELP_DETACH 148 
#define  HELP_EXPORT 147 
#define  HELP_GET 146 
#define  HELP_HISTORY 145 
#define  HELP_IMPORT 144 
#define  HELP_INITIALIZE 143 
#define  HELP_IOSTAT 142 
#define  HELP_LABELCLEAR 141 
#define  HELP_LIST 140 
#define  HELP_OFFLINE 139 
#define  HELP_ONLINE 138 
#define  HELP_REGUID 137 
#define  HELP_REMOVE 136 
#define  HELP_REOPEN 135 
#define  HELP_REPLACE 134 
#define  HELP_SCRUB 133 
#define  HELP_SET 132 
#define  HELP_SPLIT 131 
#define  HELP_STATUS 130 
#define  HELP_SYNC 129 
#define  HELP_UPGRADE 128 
 int /*<<< orphan*/  abort () ; 
 char const* gettext (char*) ; 

__attribute__((used)) static const char *
get_usage(zpool_help_t idx)
{
	switch (idx) {
	case HELP_ADD:
		return (gettext("\tadd [-fn] <pool> <vdev> ...\n"));
	case HELP_ATTACH:
		return (gettext("\tattach [-f] <pool> <device> "
		    "<new-device>\n"));
	case HELP_CLEAR:
		return (gettext("\tclear [-nF] <pool> [device]\n"));
	case HELP_CREATE:
		return (gettext("\tcreate [-fnd] [-B] "
		    "[-o property=value] ... \n"
		    "\t    [-O file-system-property=value] ...\n"
		    "\t    [-m mountpoint] [-R root] [-t tempname] "
		    "<pool> <vdev> ...\n"));
	case HELP_CHECKPOINT:
		return (gettext("\tcheckpoint [--discard] <pool> ...\n"));
	case HELP_DESTROY:
		return (gettext("\tdestroy [-f] <pool>\n"));
	case HELP_DETACH:
		return (gettext("\tdetach <pool> <device>\n"));
	case HELP_EXPORT:
		return (gettext("\texport [-f] <pool> ...\n"));
	case HELP_HISTORY:
		return (gettext("\thistory [-il] [<pool>] ...\n"));
	case HELP_IMPORT:
		return (gettext("\timport [-d dir] [-D]\n"
		    "\timport [-o mntopts] [-o property=value] ... \n"
		    "\t    [-d dir | -c cachefile] [-D] [-f] [-m] [-N] "
		    "[-R root] [-F [-n]] -a\n"
		    "\timport [-o mntopts] [-o property=value] ... \n"
		    "\t    [-d dir | -c cachefile] [-D] [-f] [-m] [-N] "
		    "[-R root] [-F [-n]] [-t]\n"
		    "\t    [--rewind-to-checkpoint] <pool | id> [newpool]\n"));
	case HELP_IOSTAT:
		return (gettext("\tiostat [-v] [-T d|u] [pool] ... [interval "
		    "[count]]\n"));
	case HELP_LABELCLEAR:
		return (gettext("\tlabelclear [-f] <vdev>\n"));
	case HELP_LIST:
		return (gettext("\tlist [-Hpv] [-o property[,...]] "
		    "[-T d|u] [pool] ... [interval [count]]\n"));
	case HELP_OFFLINE:
		return (gettext("\toffline [-t] <pool> <device> ...\n"));
	case HELP_ONLINE:
		return (gettext("\tonline [-e] <pool> <device> ...\n"));
	case HELP_REPLACE:
		return (gettext("\treplace [-f] <pool> <device> "
		    "[new-device]\n"));
	case HELP_REMOVE:
		return (gettext("\tremove [-nps] <pool> <device> ...\n"));
	case HELP_REOPEN:
		return (gettext("\treopen <pool>\n"));
	case HELP_INITIALIZE:
		return (gettext("\tinitialize [-cs] <pool> [<device> ...]\n"));
	case HELP_SCRUB:
		return (gettext("\tscrub [-s | -p] <pool> ...\n"));
	case HELP_STATUS:
		return (gettext("\tstatus [-vx] [-T d|u] [pool] ... [interval "
		    "[count]]\n"));
	case HELP_UPGRADE:
		return (gettext("\tupgrade [-v]\n"
		    "\tupgrade [-V version] <-a | pool ...>\n"));
	case HELP_GET:
		return (gettext("\tget [-Hp] [-o \"all\" | field[,...]] "
		    "<\"all\" | property[,...]> <pool> ...\n"));
	case HELP_SET:
		return (gettext("\tset <property=value> <pool> \n"));
	case HELP_SPLIT:
		return (gettext("\tsplit [-n] [-R altroot] [-o mntopts]\n"
		    "\t    [-o property=value] <pool> <newpool> "
		    "[<device> ...]\n"));
	case HELP_REGUID:
		return (gettext("\treguid <pool>\n"));
	case HELP_SYNC:
		return (gettext("\tsync [pool] ...\n"));
	}

	abort();
	/* NOTREACHED */
}