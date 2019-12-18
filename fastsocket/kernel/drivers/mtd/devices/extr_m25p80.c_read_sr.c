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
typedef  int u8 ;
struct m25p {TYPE_1__* spi; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int OPCODE_RDSR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ spi_write_then_read (TYPE_1__*,int*,int,int*,int) ; 

__attribute__((used)) static int read_sr(struct m25p *flash)
{
	ssize_t retval;
	u8 code = OPCODE_RDSR;
	u8 val;

	retval = spi_write_then_read(flash->spi, &code, 1, &val, 1);

	if (retval < 0) {
		dev_err(&flash->spi->dev, "error %d reading SR\n",
				(int) retval);
		return retval;
	}

	return val;
}