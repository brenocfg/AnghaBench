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
typedef  int u16 ;
struct dvb_frontend {struct bcm3510_state* demodulator_priv; } ;
struct TYPE_2__ {int SIGNAL; } ;
struct bcm3510_state {TYPE_1__ status2; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  bcm3510_refresh_state (struct bcm3510_state*) ; 

__attribute__((used)) static int bcm3510_read_signal_strength(struct dvb_frontend* fe, u16* strength)
{
	struct bcm3510_state* st = fe->demodulator_priv;
	s32 t;

	bcm3510_refresh_state(st);
	t = st->status2.SIGNAL;

	if (t > 190)
		t = 190;
	if (t < 90)
		t = 90;

	t -= 90;
	t = t * 0xff / 100;
	/* normalize if necessary */
	*strength = (t << 8) | t;
	return 0;
}