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
typedef  int /*<<< orphan*/  VARENT ;
struct TYPE_3__ {char* ki_args; } ;
typedef  TYPE_1__ KINFO ;

/* Variables and functions */
 size_t ARGUMENTS_WIDTH ; 
 int /*<<< orphan*/ * STAILQ_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int VIS_NL ; 
 int VIS_NOSLASH ; 
 int VIS_TAB ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  next_ve ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strvis (char*,char*,int) ; 
 int /*<<< orphan*/  xo_errx (int,char*) ; 

char *
arguments(KINFO *k, VARENT *ve)
{
	char *vis_args;

	if ((vis_args = malloc(strlen(k->ki_args) * 4 + 1)) == NULL)
		xo_errx(1, "malloc failed");
	strvis(vis_args, k->ki_args, VIS_TAB | VIS_NL | VIS_NOSLASH);

	if (STAILQ_NEXT(ve, next_ve) != NULL && strlen(vis_args) > ARGUMENTS_WIDTH)
		vis_args[ARGUMENTS_WIDTH] = '\0';

	return (vis_args);
}