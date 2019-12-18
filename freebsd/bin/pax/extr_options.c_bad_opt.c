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
struct TYPE_3__ {char* name; char* value; } ;
typedef  TYPE_1__ OPLIST ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/ * ophead ; 
 TYPE_1__* opt_next () ; 
 int /*<<< orphan*/  pax_usage () ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 int /*<<< orphan*/  stderr ; 

int
bad_opt(void)
{
	OPLIST *opt;

	if (ophead == NULL)
		return(0);
	/*
	 * print all we were given
	 */
	paxwarn(1,"These format options are not supported");
	while ((opt = opt_next()) != NULL)
		(void)fprintf(stderr, "\t%s = %s\n", opt->name, opt->value);
	pax_usage();
	return(0);
}