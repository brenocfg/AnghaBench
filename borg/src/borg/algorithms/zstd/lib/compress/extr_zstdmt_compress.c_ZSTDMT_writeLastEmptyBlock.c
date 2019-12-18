#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ capacity; int /*<<< orphan*/ * start; } ;
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_5__ {int lastJob; scalar_t__ firstJob; scalar_t__ consumed; int /*<<< orphan*/  cSize; TYPE_4__ dstBuff; TYPE_2__ src; int /*<<< orphan*/  bufPool; } ;
typedef  TYPE_1__ ZSTDMT_jobDescription ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (int /*<<< orphan*/ ) ; 
 TYPE_4__ ZSTDMT_getBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_blockHeaderSize ; 
 int /*<<< orphan*/  ZSTD_isError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_writeLastEmptyBlock (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__ kNullRange ; 
 int /*<<< orphan*/  memory_allocation ; 

__attribute__((used)) static void ZSTDMT_writeLastEmptyBlock(ZSTDMT_jobDescription* job)
{
    assert(job->lastJob == 1);
    assert(job->src.size == 0);   /* last job is empty -> will be simplified into a last empty block */
    assert(job->firstJob == 0);   /* cannot be first job, as it also needs to create frame header */
    assert(job->dstBuff.start == NULL);   /* invoked from streaming variant only (otherwise, dstBuff might be user's output) */
    job->dstBuff = ZSTDMT_getBuffer(job->bufPool);
    if (job->dstBuff.start == NULL) {
      job->cSize = ERROR(memory_allocation);
      return;
    }
    assert(job->dstBuff.capacity >= ZSTD_blockHeaderSize);   /* no buffer should ever be that small */
    job->src = kNullRange;
    job->cSize = ZSTD_writeLastEmptyBlock(job->dstBuff.start, job->dstBuff.capacity);
    assert(!ZSTD_isError(job->cSize));
    assert(job->consumed == 0);
}