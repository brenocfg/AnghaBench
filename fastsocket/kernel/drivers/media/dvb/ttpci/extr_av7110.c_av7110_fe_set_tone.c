#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dvb_frontend {TYPE_1__* dvb; } ;
struct av7110 {int (* fe_set_tone ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  saved_tone; } ;
typedef  int /*<<< orphan*/  fe_sec_tone_mode_t ;
struct TYPE_2__ {struct av7110* priv; } ;

/* Variables and functions */
 int av7110_fe_lock_fix (struct av7110*,int /*<<< orphan*/ ) ; 
 int stub1 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int av7110_fe_set_tone(struct dvb_frontend* fe, fe_sec_tone_mode_t tone)
{
	struct av7110* av7110 = fe->dvb->priv;

	int ret = av7110_fe_lock_fix(av7110, 0);
	if (!ret) {
		av7110->saved_tone = tone;
		ret = av7110->fe_set_tone(fe, tone);
	}
	return ret;
}