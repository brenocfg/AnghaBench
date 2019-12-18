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
struct TYPE_4__ {scalar_t__ uud_name; } ;
typedef  TYPE_1__ uu_dprintf_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  uu_free (TYPE_1__*) ; 

void
uu_dprintf_destroy(uu_dprintf_t *D)
{
	if (D->uud_name)
		free(D->uud_name);

	uu_free(D);
}