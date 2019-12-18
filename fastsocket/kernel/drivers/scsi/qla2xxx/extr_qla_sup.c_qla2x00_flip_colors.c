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
typedef  int /*<<< orphan*/  uint16_t ;
struct qla_hw_data {scalar_t__ beacon_color_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_LED_ALL_OFF ; 
 int /*<<< orphan*/  GPIO_LED_GREEN_OFF_AMBER_OFF ; 
 int /*<<< orphan*/  GPIO_LED_GREEN_ON_AMBER_OFF ; 
 int /*<<< orphan*/  GPIO_LED_RGA_ON ; 
 scalar_t__ IS_QLA2322 (struct qla_hw_data*) ; 
 scalar_t__ QLA_LED_ALL_ON ; 
 scalar_t__ QLA_LED_GRN_ON ; 

__attribute__((used)) static inline void
qla2x00_flip_colors(struct qla_hw_data *ha, uint16_t *pflags)
{
	if (IS_QLA2322(ha)) {
		/* Flip all colors. */
		if (ha->beacon_color_state == QLA_LED_ALL_ON) {
			/* Turn off. */
			ha->beacon_color_state = 0;
			*pflags = GPIO_LED_ALL_OFF;
		} else {
			/* Turn on. */
			ha->beacon_color_state = QLA_LED_ALL_ON;
			*pflags = GPIO_LED_RGA_ON;
		}
	} else {
		/* Flip green led only. */
		if (ha->beacon_color_state == QLA_LED_GRN_ON) {
			/* Turn off. */
			ha->beacon_color_state = 0;
			*pflags = GPIO_LED_GREEN_OFF_AMBER_OFF;
		} else {
			/* Turn on. */
			ha->beacon_color_state = QLA_LED_GRN_ON;
			*pflags = GPIO_LED_GREEN_ON_AMBER_OFF;
		}
	}
}