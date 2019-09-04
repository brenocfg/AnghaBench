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
struct TYPE_3__ {int cdt_expirations; scalar_t__ _active_count; scalar_t__ total_packets; scalar_t__ errors; } ;
typedef  TYPE_1__ hdcd_detection_data ;

/* Variables and functions */

__attribute__((used)) static void hdcd_detect_start(hdcd_detection_data *detect) {
    detect->errors = 0;          /* re-sum every pass */
    detect->total_packets = 0;
    detect->_active_count = 0;   /* will need to match channels at hdcd_detect_end() */
    detect->cdt_expirations = -1;
}