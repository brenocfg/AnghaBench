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
struct wps_registrar {int dummy; } ;

/* Variables and functions */
 int wps_set_ie (struct wps_registrar*) ; 

int wps_registrar_update_ie(struct wps_registrar *reg)
{
	return wps_set_ie(reg);
}