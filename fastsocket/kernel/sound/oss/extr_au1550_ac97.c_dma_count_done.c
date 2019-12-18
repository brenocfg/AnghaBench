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
struct dmabuf {int dma_fragsize; int /*<<< orphan*/  dmanr; scalar_t__ stopped; } ;

/* Variables and functions */
 int au1xxx_get_dma_residue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dma_count_done(struct dmabuf *db)
{
	if (db->stopped)
		return 0;

	return db->dma_fragsize - au1xxx_get_dma_residue(db->dmanr);
}