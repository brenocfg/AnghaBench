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

/* Variables and functions */
 int /*<<< orphan*/  done (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,char*) ; 
 char* input_file_name ; 
 int lineno ; 
 char* myname ; 
 int /*<<< orphan*/  stderr ; 

void
untyped_lhs(void)
{
    fprintf(stderr, "%s: e - line %d of \"%s\", $$ is untyped\n",
	    myname, lineno, input_file_name);
    done(1);
}