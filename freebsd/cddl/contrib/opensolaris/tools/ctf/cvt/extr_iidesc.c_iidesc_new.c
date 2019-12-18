#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ii_name; } ;
typedef  TYPE_1__ iidesc_t ;

/* Variables and functions */
 TYPE_1__* xcalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

iidesc_t *
iidesc_new(char *name)
{
	iidesc_t *ii;

	ii = xcalloc(sizeof (iidesc_t));
	if (name)
		ii->ii_name = xstrdup(name);

	return (ii);
}