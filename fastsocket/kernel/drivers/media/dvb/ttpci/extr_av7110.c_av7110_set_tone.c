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
struct av7110 {int dummy; } ;
typedef  int fe_sec_tone_mode_t ;
struct TYPE_2__ {struct av7110* priv; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SEC_TONE_OFF 129 
#define  SEC_TONE_ON 128 
 int Set22K (struct av7110*,int) ; 

__attribute__((used)) static int av7110_set_tone(struct dvb_frontend* fe, fe_sec_tone_mode_t tone)
{
	struct av7110* av7110 = fe->dvb->priv;

	switch (tone) {
	case SEC_TONE_ON:
		return Set22K(av7110, 1);

	case SEC_TONE_OFF:
		return Set22K(av7110, 0);

	default:
		return -EINVAL;
	}
}