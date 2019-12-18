#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int state; int n2count; int n2; int /*<<< orphan*/  modulus; TYPE_1__* ax25_dev; int /*<<< orphan*/  window; } ;
typedef  TYPE_2__ ax25_cb ;
struct TYPE_9__ {int /*<<< orphan*/ * values; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_COMMAND ; 
 int /*<<< orphan*/  AX25_DISC ; 
 int /*<<< orphan*/  AX25_DM ; 
 int /*<<< orphan*/  AX25_MODULUS ; 
 int /*<<< orphan*/  AX25_POLLON ; 
 int /*<<< orphan*/  AX25_RESPONSE ; 
 int /*<<< orphan*/  AX25_SABM ; 
 int /*<<< orphan*/  AX25_SABME ; 
#define  AX25_STATE_1 131 
#define  AX25_STATE_2 130 
#define  AX25_STATE_3 129 
#define  AX25_STATE_4 128 
 size_t AX25_VALUES_WINDOW ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  ax25_calculate_t1 (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_disconnect (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax25_send_control (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax25_start_t1timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_std_transmit_enquiry (TYPE_2__*) ; 

void ax25_std_t1timer_expiry(ax25_cb *ax25)
{
	switch (ax25->state) {
	case AX25_STATE_1:
		if (ax25->n2count == ax25->n2) {
			if (ax25->modulus == AX25_MODULUS) {
				ax25_disconnect(ax25, ETIMEDOUT);
				return;
			} else {
				ax25->modulus = AX25_MODULUS;
				ax25->window  = ax25->ax25_dev->values[AX25_VALUES_WINDOW];
				ax25->n2count = 0;
				ax25_send_control(ax25, AX25_SABM, AX25_POLLON, AX25_COMMAND);
			}
		} else {
			ax25->n2count++;
			if (ax25->modulus == AX25_MODULUS)
				ax25_send_control(ax25, AX25_SABM, AX25_POLLON, AX25_COMMAND);
			else
				ax25_send_control(ax25, AX25_SABME, AX25_POLLON, AX25_COMMAND);
		}
		break;

	case AX25_STATE_2:
		if (ax25->n2count == ax25->n2) {
			ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
			ax25_disconnect(ax25, ETIMEDOUT);
			return;
		} else {
			ax25->n2count++;
			ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
		}
		break;

	case AX25_STATE_3:
		ax25->n2count = 1;
		ax25_std_transmit_enquiry(ax25);
		ax25->state   = AX25_STATE_4;
		break;

	case AX25_STATE_4:
		if (ax25->n2count == ax25->n2) {
			ax25_send_control(ax25, AX25_DM, AX25_POLLON, AX25_RESPONSE);
			ax25_disconnect(ax25, ETIMEDOUT);
			return;
		} else {
			ax25->n2count++;
			ax25_std_transmit_enquiry(ax25);
		}
		break;
	}

	ax25_calculate_t1(ax25);
	ax25_start_t1timer(ax25);
}