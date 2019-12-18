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
struct lgs8gxx_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lgs8gxx_write_reg (struct lgs8gxx_state*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int lgs8gxx_soft_reset(struct lgs8gxx_state *priv)
{
	lgs8gxx_write_reg(priv, 0x02, 0x00);
	msleep(1);
	lgs8gxx_write_reg(priv, 0x02, 0x01);
	msleep(100);

	return 0;
}