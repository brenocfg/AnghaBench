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
 int ESP_FAIL ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  gWpsSm ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int wps_tx_start () ; 

int wps_start_pending(void)
{
    if (!gWpsSm) {
        return ESP_FAIL;
    }

    wpa_printf(MSG_DEBUG, "wps start pending");
    return wps_tx_start();
}