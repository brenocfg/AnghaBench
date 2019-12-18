#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_2__ {scalar_t__ et_type; int /*<<< orphan*/ * et_name; } ;

/* Variables and functions */
 TYPE_1__* elements ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static u_int16_t
parse_element_type(char *cp)
{
	int i;

	for (i = 0; elements[i].et_name != NULL; ++i)
		if (strcmp(elements[i].et_name, cp) == 0)
			return ((u_int16_t)elements[i].et_type);

	errx(1, "invalid element type `%s'", cp);
	/* NOTREACHED */
}