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
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_registrar_stop_pbc (struct wps_registrar*) ; 

__attribute__((used)) static void wps_registrar_pbc_completed(struct wps_registrar *reg)
{
	wpa_printf(MSG_DEBUG,  "WPS: PBC completed - stopping PBC mode");

	wps_registrar_stop_pbc(reg);
}