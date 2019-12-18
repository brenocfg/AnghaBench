#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  io_data; int /*<<< orphan*/  io_addr; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ board_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM9000_NCR ; 
 int /*<<< orphan*/  NCR_RST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dm9000_reset(board_info_t * db)
{
	dev_dbg(db->dev, "resetting device\n");

	/* RESET device */
	writeb(DM9000_NCR, db->io_addr);
	udelay(200);
	writeb(NCR_RST, db->io_data);
	udelay(200);
}