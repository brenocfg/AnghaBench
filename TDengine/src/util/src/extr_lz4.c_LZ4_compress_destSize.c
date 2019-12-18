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
typedef  int /*<<< orphan*/  LZ4_stream_t ;

/* Variables and functions */
 scalar_t__ ALLOCATOR (int,int) ; 
 int /*<<< orphan*/  FREEMEM (int /*<<< orphan*/ *) ; 
 int LZ4_compress_destSize_extState (int /*<<< orphan*/ *,char const*,char*,int*,int) ; 

int LZ4_compress_destSize(const char* src, char* dst, int* srcSizePtr, int targetDstSize)
{
#if (LZ4_HEAPMODE)
    LZ4_stream_t* ctx = (LZ4_stream_t*)ALLOCATOR(1, sizeof(LZ4_stream_t));   /* malloc-calloc always properly aligned */
#else
    LZ4_stream_t ctxBody;
    LZ4_stream_t* ctx = &ctxBody;
#endif

    int result = LZ4_compress_destSize_extState(ctx, src, dst, srcSizePtr, targetDstSize);

#if (LZ4_HEAPMODE)
    FREEMEM(ctx);
#endif
    return result;
}