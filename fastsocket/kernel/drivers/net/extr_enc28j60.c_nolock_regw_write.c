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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct enc28j60_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENC28J60_WRITE_CTRL_REG ; 
 int /*<<< orphan*/  enc28j60_set_bank (struct enc28j60_net*,scalar_t__) ; 
 int /*<<< orphan*/  spi_write_op (struct enc28j60_net*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void nolock_regw_write(struct enc28j60_net *priv,
				       u8 address, u16 data)
{
	enc28j60_set_bank(priv, address);
	spi_write_op(priv, ENC28J60_WRITE_CTRL_REG, address, (u8) data);
	spi_write_op(priv, ENC28J60_WRITE_CTRL_REG, address + 1,
		     (u8) (data >> 8));
}