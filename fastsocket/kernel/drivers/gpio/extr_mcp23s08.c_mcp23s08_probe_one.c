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
typedef  unsigned int u8 ;
typedef  int /*<<< orphan*/  tx ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct mcp23s08_driver_data {struct mcp23s08** mcp; } ;
struct TYPE_2__ {char* label; unsigned int base; int ngpio; int can_sleep; int /*<<< orphan*/  owner; int /*<<< orphan*/ * dev; int /*<<< orphan*/  dbg_show; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_input; } ;
struct mcp23s08 {int addr; scalar_t__* cache; TYPE_1__ chip; struct spi_device* spi; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int IOCON_HAEN ; 
 int IOCON_SEQOP ; 
 size_t MCP_GPINTEN ; 
 int /*<<< orphan*/  MCP_GPPU ; 
 int /*<<< orphan*/  MCP_IOCON ; 
 size_t MCP_IPOL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 int gpiochip_add (TYPE_1__*) ; 
 int /*<<< orphan*/  mcp23s08_dbg_show ; 
 int /*<<< orphan*/  mcp23s08_direction_input ; 
 int /*<<< orphan*/  mcp23s08_direction_output ; 
 int /*<<< orphan*/  mcp23s08_get ; 
 int mcp23s08_read (struct mcp23s08*,int /*<<< orphan*/ ) ; 
 int mcp23s08_read_regs (struct mcp23s08*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  mcp23s08_set ; 
 int mcp23s08_write (struct mcp23s08*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,scalar_t__*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct mcp23s08_driver_data* spi_get_drvdata (struct spi_device*) ; 
 int spi_write_then_read (struct spi_device*,unsigned int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcp23s08_probe_one(struct spi_device *spi, unsigned addr,
		unsigned base, unsigned pullups)
{
	struct mcp23s08_driver_data	*data = spi_get_drvdata(spi);
	struct mcp23s08			*mcp = data->mcp[addr];
	int				status;
	int				do_update = 0;

	mutex_init(&mcp->lock);

	mcp->spi = spi;
	mcp->addr = 0x40 | (addr << 1);

	mcp->chip.label = "mcp23s08",

	mcp->chip.direction_input = mcp23s08_direction_input;
	mcp->chip.get = mcp23s08_get;
	mcp->chip.direction_output = mcp23s08_direction_output;
	mcp->chip.set = mcp23s08_set;
	mcp->chip.dbg_show = mcp23s08_dbg_show;

	mcp->chip.base = base;
	mcp->chip.ngpio = 8;
	mcp->chip.can_sleep = 1;
	mcp->chip.dev = &spi->dev;
	mcp->chip.owner = THIS_MODULE;

	/* verify MCP_IOCON.SEQOP = 0, so sequential reads work,
	 * and MCP_IOCON.HAEN = 1, so we work with all chips.
	 */
	status = mcp23s08_read(mcp, MCP_IOCON);
	if (status < 0)
		goto fail;
	if ((status & IOCON_SEQOP) || !(status & IOCON_HAEN)) {
		status &= ~IOCON_SEQOP;
		status |= IOCON_HAEN;
		status = mcp23s08_write(mcp, MCP_IOCON, (u8) status);
		if (status < 0)
			goto fail;
	}

	/* configure ~100K pullups */
	status = mcp23s08_write(mcp, MCP_GPPU, pullups);
	if (status < 0)
		goto fail;

	status = mcp23s08_read_regs(mcp, 0, mcp->cache, sizeof mcp->cache);
	if (status < 0)
		goto fail;

	/* disable inverter on input */
	if (mcp->cache[MCP_IPOL] != 0) {
		mcp->cache[MCP_IPOL] = 0;
		do_update = 1;
	}

	/* disable irqs */
	if (mcp->cache[MCP_GPINTEN] != 0) {
		mcp->cache[MCP_GPINTEN] = 0;
		do_update = 1;
	}

	if (do_update) {
		u8 tx[4];

		tx[0] = mcp->addr;
		tx[1] = MCP_IPOL;
		memcpy(&tx[2], &mcp->cache[MCP_IPOL], sizeof(tx) - 2);
		status = spi_write_then_read(mcp->spi, tx, sizeof tx, NULL, 0);
		if (status < 0)
			goto fail;
	}

	status = gpiochip_add(&mcp->chip);
fail:
	if (status < 0)
		dev_dbg(&spi->dev, "can't setup chip %d, --> %d\n",
				addr, status);
	return status;
}