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
 int /*<<< orphan*/  SIG_WPA2_START ; 
 int wpa2_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wpa2_start_eapol_internal () ; 

__attribute__((used)) static int wpa2_start_eapol(void)
{
#ifdef USE_WPA2_TASK
    return wpa2_post(SIG_WPA2_START, 0);
#else
    return wpa2_start_eapol_internal();
#endif
}