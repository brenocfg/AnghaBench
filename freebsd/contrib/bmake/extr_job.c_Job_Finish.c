#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  children; int /*<<< orphan*/  commands; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  JobRun (TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int errors ; 
 TYPE_1__* postCommands ; 

int
Job_Finish(void)
{
    if (postCommands != NULL &&
	(!Lst_IsEmpty(postCommands->commands) ||
	 !Lst_IsEmpty(postCommands->children))) {
	if (errors) {
	    Error("Errors reported so .END ignored");
	} else {
	    JobRun(postCommands);
	}
    }
    return(errors);
}