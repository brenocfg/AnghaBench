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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* CONCAT1 (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ CountLine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  YYINT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  outline ; 

__attribute__((used)) static void
output_YYINT_typedef(FILE * fp)
{
    /* generate the type used to index the various parser tables */
    if (CountLine(fp))
	++outline;
    fprintf(fp, "typedef %s YYINT;\n", CONCAT1("", YYINT));
}