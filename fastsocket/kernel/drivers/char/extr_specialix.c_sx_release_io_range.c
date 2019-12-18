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
struct specialix_board {int flags; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int SX_BOARD_IS_PCI ; 
 int /*<<< orphan*/  SX_IO_SPACE ; 
 int /*<<< orphan*/  SX_PCI_IO_SPACE ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sx_release_io_range(struct specialix_board *bp)
{
	release_region(bp->base, bp->flags & SX_BOARD_IS_PCI ?
					SX_PCI_IO_SPACE : SX_IO_SPACE);
}