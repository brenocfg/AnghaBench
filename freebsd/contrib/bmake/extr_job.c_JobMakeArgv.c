#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  args ;
struct TYPE_5__ {char* exit; char* echo; } ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int JOB_IGNERR ; 
 int JOB_SILENT ; 
 char* UNCONST (char*) ; 
 TYPE_2__* commandShell ; 
 char* shellName ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static void
JobMakeArgv(Job *job, char **argv)
{
    int	    	  argc;
    static char args[10]; 	/* For merged arguments */

    argv[0] = UNCONST(shellName);
    argc = 1;

    if ((commandShell->exit && (*commandShell->exit != '-')) ||
	(commandShell->echo && (*commandShell->echo != '-')))
    {
	/*
	 * At least one of the flags doesn't have a minus before it, so
	 * merge them together. Have to do this because the *(&(@*#*&#$#
	 * Bourne shell thinks its second argument is a file to source.
	 * Grrrr. Note the ten-character limitation on the combined arguments.
	 */
	(void)snprintf(args, sizeof(args), "-%s%s",
		      ((job->flags & JOB_IGNERR) ? "" :
		       (commandShell->exit ? commandShell->exit : "")),
		      ((job->flags & JOB_SILENT) ? "" :
		       (commandShell->echo ? commandShell->echo : "")));

	if (args[1]) {
	    argv[argc] = args;
	    argc++;
	}
    } else {
	if (!(job->flags & JOB_IGNERR) && commandShell->exit) {
	    argv[argc] = UNCONST(commandShell->exit);
	    argc++;
	}
	if (!(job->flags & JOB_SILENT) && commandShell->echo) {
	    argv[argc] = UNCONST(commandShell->echo);
	    argc++;
	}
    }
    argv[argc] = NULL;
}