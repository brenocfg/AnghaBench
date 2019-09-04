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
struct TYPE_3__ {int _active_count; int /*<<< orphan*/  hdcd_detected; scalar_t__ peak_extend; scalar_t__ max_gain_adjustment; } ;
typedef  TYPE_1__ hdcd_detection_data ;

/* Variables and functions */
 int /*<<< orphan*/  HDCD_EFFECTUAL ; 
 int /*<<< orphan*/  HDCD_NO_EFFECT ; 

__attribute__((used)) static void hdcd_detect_end(hdcd_detection_data *detect, int channels) {
    /* HDCD is detected if a valid packet is active in all
     * channels at the same time. */
    if (detect->_active_count == channels) {
        if (detect->max_gain_adjustment || detect->peak_extend)
            detect->hdcd_detected = HDCD_EFFECTUAL;
        else
            detect->hdcd_detected = HDCD_NO_EFFECT;
    }
}