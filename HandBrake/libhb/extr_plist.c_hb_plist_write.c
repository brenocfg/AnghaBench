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
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  gval_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* postfix ; 
 char* preamble ; 

void
hb_plist_write(FILE *file, hb_value_t *gval)
{
    fprintf(file, "%s", preamble);
    gval_write(file, gval);
    fprintf(file, "%s", postfix);
}