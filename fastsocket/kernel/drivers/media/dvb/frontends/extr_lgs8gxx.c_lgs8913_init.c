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
typedef  int u8 ;
struct lgs8gxx_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lgs8gxx_read_reg (struct lgs8gxx_state*,int,int*) ; 
 int /*<<< orphan*/  lgs8gxx_write_reg (struct lgs8gxx_state*,int,int) ; 

__attribute__((used)) static int lgs8913_init(struct lgs8gxx_state *priv)
{
	u8 t;

	/* LGS8913 specific */
	lgs8gxx_write_reg(priv, 0xc1, 0x3);

	lgs8gxx_read_reg(priv, 0x7c, &t);
	lgs8gxx_write_reg(priv, 0x7c, (t&0x8c) | 0x3);

	/* LGS8913 specific */
	lgs8gxx_read_reg(priv, 0xc3, &t);
	lgs8gxx_write_reg(priv, 0xc3, t&0x10);


	return 0;
}