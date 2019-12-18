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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 size_t BLKIO_STAT_ASYNC ; 
 size_t BLKIO_STAT_READ ; 
 size_t BLKIO_STAT_SYNC ; 
 size_t BLKIO_STAT_WRITE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static void blkio_check_and_dec_stat(uint64_t *stat, bool direction, bool sync)
{
	if (direction) {
		BUG_ON(stat[BLKIO_STAT_WRITE] == 0);
		stat[BLKIO_STAT_WRITE]--;
	} else {
		BUG_ON(stat[BLKIO_STAT_READ] == 0);
		stat[BLKIO_STAT_READ]--;
	}
	if (sync) {
		BUG_ON(stat[BLKIO_STAT_SYNC] == 0);
		stat[BLKIO_STAT_SYNC]--;
	} else {
		BUG_ON(stat[BLKIO_STAT_ASYNC] == 0);
		stat[BLKIO_STAT_ASYNC]--;
	}
}