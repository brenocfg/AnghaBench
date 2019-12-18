#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_outBuffer ;
typedef  int /*<<< orphan*/  ZSTD_inBuffer ;
struct TYPE_5__ {size_t filled; } ;
struct TYPE_6__ {size_t targetSectionSize; TYPE_1__ inBuff; } ;
typedef  TYPE_2__ ZSTDMT_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDMT_compressStream_generic (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_e_continue ; 

size_t ZSTDMT_compressStream(ZSTDMT_CCtx* mtctx, ZSTD_outBuffer* output, ZSTD_inBuffer* input)
{
    CHECK_F( ZSTDMT_compressStream_generic(mtctx, output, input, ZSTD_e_continue) );

    /* recommended next input size : fill current input buffer */
    return mtctx->targetSectionSize - mtctx->inBuff.filled;   /* note : could be zero when input buffer is fully filled and no more availability to create new job */
}