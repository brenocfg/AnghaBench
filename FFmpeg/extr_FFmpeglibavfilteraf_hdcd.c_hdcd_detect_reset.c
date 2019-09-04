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
struct TYPE_3__ {double max_gain_adjustment; int cdt_expirations; scalar_t__ _active_count; scalar_t__ uses_transient_filter; int /*<<< orphan*/  peak_extend; scalar_t__ errors; scalar_t__ total_packets; int /*<<< orphan*/  packet_type; int /*<<< orphan*/  hdcd_detected; } ;
typedef  TYPE_1__ hdcd_detection_data ;

/* Variables and functions */
 int /*<<< orphan*/  HDCD_NONE ; 
 int /*<<< orphan*/  HDCD_PE_NEVER ; 
 int /*<<< orphan*/  HDCD_PVER_NONE ; 

__attribute__((used)) static void hdcd_detect_reset(hdcd_detection_data *detect) {
    detect->hdcd_detected = HDCD_NONE;
    detect->packet_type = HDCD_PVER_NONE;
    detect->total_packets = 0;
    detect->errors = 0;
    detect->peak_extend = HDCD_PE_NEVER;
    detect->uses_transient_filter = 0;
    detect->max_gain_adjustment = 0.0;
    detect->cdt_expirations = -1;
    detect->_active_count = 0;
}