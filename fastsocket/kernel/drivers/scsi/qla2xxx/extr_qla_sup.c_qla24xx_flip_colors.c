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
typedef  int uint16_t ;
struct qla_hw_data {scalar_t__ beacon_color_state; } ;

/* Variables and functions */
 int GPDX_LED_AMBER_ON ; 
 int GPDX_LED_YELLOW_ON ; 
 scalar_t__ QLA_LED_ALL_ON ; 

__attribute__((used)) static inline void
qla24xx_flip_colors(struct qla_hw_data *ha, uint16_t *pflags)
{
	/* Flip all colors. */
	if (ha->beacon_color_state == QLA_LED_ALL_ON) {
		/* Turn off. */
		ha->beacon_color_state = 0;
		*pflags = 0;
	} else {
		/* Turn on. */
		ha->beacon_color_state = QLA_LED_ALL_ON;
		*pflags = GPDX_LED_YELLOW_ON | GPDX_LED_AMBER_ON;
	}
}