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
typedef  int /*<<< orphan*/  ZSTDMT_seqPool ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTDMT_expandBufferPool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ZSTDMT_seqPool* ZSTDMT_expandSeqPool(ZSTDMT_seqPool* pool, U32 nbWorkers)
{
    return ZSTDMT_expandBufferPool(pool, nbWorkers);
}