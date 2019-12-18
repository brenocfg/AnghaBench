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
typedef  int uint32_t ;

/* Variables and functions */
 int Isconnecting ; 
 int /*<<< orphan*/  esp_ble_gap_start_scanning (int) ; 
 int stop_scan_done ; 

__attribute__((used)) static void start_scan(void)
{
    stop_scan_done = false;
    Isconnecting = false;
    uint32_t duration = 30;
    esp_ble_gap_start_scanning(duration);
}