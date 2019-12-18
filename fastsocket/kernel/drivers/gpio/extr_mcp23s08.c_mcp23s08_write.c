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
typedef  unsigned int u8 ;
struct mcp23s08 {unsigned int addr; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int spi_write_then_read (int /*<<< orphan*/ ,unsigned int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcp23s08_write(struct mcp23s08 *mcp, unsigned reg, u8 val)
{
	u8	tx[3];

	tx[0] = mcp->addr;
	tx[1] = reg;
	tx[2] = val;
	return spi_write_then_read(mcp->spi, tx, sizeof tx, NULL, 0);
}