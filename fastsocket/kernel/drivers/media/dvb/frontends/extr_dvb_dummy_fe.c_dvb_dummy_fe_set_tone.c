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
struct dvb_frontend {int dummy; } ;
typedef  int /*<<< orphan*/  fe_sec_tone_mode_t ;

/* Variables and functions */

__attribute__((used)) static int dvb_dummy_fe_set_tone(struct dvb_frontend* fe, fe_sec_tone_mode_t tone)
{
	return 0;
}