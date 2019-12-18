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
struct isi_board {int status; } ;

/* Variables and functions */
 int BOARD_ACTIVE ; 

__attribute__((used)) static inline void isicom_shutdown_board(struct isi_board *bp)
{
	if (bp->status & BOARD_ACTIVE)
		bp->status &= ~BOARD_ACTIVE;
}