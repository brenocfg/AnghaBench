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
struct quad_buffer_head {int /*<<< orphan*/  data; int /*<<< orphan*/ * bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void hpfs_brelse4(struct quad_buffer_head *qbh)
{
	brelse(qbh->bh[3]);
	brelse(qbh->bh[2]);
	brelse(qbh->bh[1]);
	brelse(qbh->bh[0]);
	kfree(qbh->data);
}