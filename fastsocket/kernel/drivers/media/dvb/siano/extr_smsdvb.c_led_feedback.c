#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ BER; } ;
struct TYPE_4__ {TYPE_1__ ReceptionData; } ;
struct smsdvb_client_t {int fe_status; int /*<<< orphan*/  coredev; TYPE_2__ sms_stat_dvb; } ;

/* Variables and functions */
 int FE_HAS_LOCK ; 
 int /*<<< orphan*/  SMS_LED_HI ; 
 int /*<<< orphan*/  SMS_LED_LO ; 
 int /*<<< orphan*/  SMS_LED_OFF ; 
 int sms_board_led_feedback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int led_feedback(struct smsdvb_client_t *client)
{
	if (client->fe_status & FE_HAS_LOCK)
		return sms_board_led_feedback(client->coredev,
			(client->sms_stat_dvb.ReceptionData.BER
			== 0) ? SMS_LED_HI : SMS_LED_LO);
	else
		return sms_board_led_feedback(client->coredev, SMS_LED_OFF);
}