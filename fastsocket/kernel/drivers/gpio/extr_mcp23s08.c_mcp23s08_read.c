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
struct mcp23s08 {int addr; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int spi_write_then_read (int /*<<< orphan*/ ,int*,int,int*,int) ; 

__attribute__((used)) static int mcp23s08_read(struct mcp23s08 *mcp, unsigned reg)
{
	u8	tx[2], rx[1];
	int	status;

	tx[0] = mcp->addr | 0x01;
	tx[1] = reg;
	status = spi_write_then_read(mcp->spi, tx, sizeof tx, rx, sizeof rx);
	return (status < 0) ? status : rx[0];
}