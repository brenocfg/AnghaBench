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
struct dvb_frontend_tune_settings {int min_delay_ms; int step_size; scalar_t__ max_drift; } ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sms_debug (char*) ; 

__attribute__((used)) static int smsdvb_get_tune_settings(struct dvb_frontend *fe,
				    struct dvb_frontend_tune_settings *tune)
{
	sms_debug("");

	tune->min_delay_ms = 400;
	tune->step_size = 250000;
	tune->max_drift = 0;
	return 0;
}