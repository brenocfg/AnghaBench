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
typedef  int /*<<< orphan*/  in_drv_t ;

/* Variables and functions */
 int IN_GP2X_NBUTTONS ; 
 char const* const* in_gp2x_keys ; 

__attribute__((used)) static const char * const *
in_gp2x_get_key_names(const in_drv_t *drv, int *count)
{
	*count = IN_GP2X_NBUTTONS;
	return in_gp2x_keys;
}