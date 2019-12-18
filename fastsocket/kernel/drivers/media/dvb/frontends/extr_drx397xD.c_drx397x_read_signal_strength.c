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
typedef  int u16 ;
struct dvb_frontend {struct drx397xD_state* demodulator_priv; } ;
struct TYPE_3__ {int d00; } ;
struct TYPE_4__ {TYPE_1__ ifagc; } ;
struct drx397xD_state {TYPE_2__ config; } ;

/* Variables and functions */
 int RD16 (struct drx397xD_state*,int) ; 

__attribute__((used)) static int drx397x_read_signal_strength(struct dvb_frontend *fe, u16 *strength)
{
	struct drx397xD_state *s = fe->demodulator_priv;
	int rc;

	if (s->config.ifagc.d00 == 2) {
		*strength = 0xffff;
		return 0;
	}
	rc = RD16(s, 0x0c20035);
	if (rc < 0) {
		*strength = 0;
		return 0;
	}
	rc &= 0x3ff;
	/* Signal strength is calculated using the following formula:
	 *
	 * a = 2200 * 150 / (2200 + 150);
	 * a = a * 3300 /  (a + 820);
	 * b = 2200 * 3300 / (2200 + 820);
	 * c = (((b-a) * rc) >> 10  + a) << 4;
	 * strength = ~c & 0xffff;
	 *
	 * The following does the same but with less rounding errors:
	 */
	*strength = ~(7720 + (rc * 30744 >> 10));

	return 0;
}