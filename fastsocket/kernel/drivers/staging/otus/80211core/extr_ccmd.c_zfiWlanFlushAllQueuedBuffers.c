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
typedef  int /*<<< orphan*/  zdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfAgingDefragList (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfApFlushBufferedPsFrame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfFlushVtxq (int /*<<< orphan*/ *) ; 

void zfiWlanFlushAllQueuedBuffers(zdev_t *dev)
{
	/* Flush VTxQ and MmQ */
	zfFlushVtxq(dev);
	/* Flush AP PS queues */
	zfApFlushBufferedPsFrame(dev);
	/* Free buffer in defragment list*/
	zfAgingDefragList(dev, 1);
}