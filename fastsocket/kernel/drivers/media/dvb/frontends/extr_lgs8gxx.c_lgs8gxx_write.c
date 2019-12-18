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
typedef  int /*<<< orphan*/  u8 ;
struct lgs8gxx_state {int dummy; } ;
struct dvb_frontend {struct lgs8gxx_state* demodulator_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int lgs8gxx_write_reg (struct lgs8gxx_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lgs8gxx_write(struct dvb_frontend *fe, u8 *buf, int len)
{
	struct lgs8gxx_state *priv = fe->demodulator_priv;

	if (len != 2)
		return -EINVAL;

	return lgs8gxx_write_reg(priv, buf[0], buf[1]);
}