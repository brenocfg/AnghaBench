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
typedef  int mig_who_t ;
typedef  scalar_t__ mig_which_error_t ;

/* Variables and functions */
 scalar_t__ MACH_MSG_ERROR_UNKNOWN_ID ; 
 int /*<<< orphan*/  printf (char*,int,scalar_t__,...) ; 

void
MigEventErrors(
	mig_who_t		who,
	mig_which_error_t	what,
	void			*par,
	char			*file,
	unsigned int		line)
{
    if (what == MACH_MSG_ERROR_UNKNOWN_ID)
	printf("%d|%d|%d -- %s %d\n", who, what, *(int *)par, file, line); 
    else
	printf("%d|%d|%s -- %s %d\n", who, what, (char *)par, file, line); 
}