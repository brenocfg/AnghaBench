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
struct enc28j60_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENC28J60_BIT_FIELD_CLR ; 
 int /*<<< orphan*/  enc28j60_set_bank (struct enc28j60_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_write_op (struct enc28j60_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nolock_reg_bfclr(struct enc28j60_net *priv,
				      u8 addr, u8 mask)
{
	enc28j60_set_bank(priv, addr);
	spi_write_op(priv, ENC28J60_BIT_FIELD_CLR, addr, mask);
}