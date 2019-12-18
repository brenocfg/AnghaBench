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
typedef  int /*<<< orphan*/  ZSTDv05_DCtx ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t BLOCKSIZE ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t ZSTDv05_decodeLiteralsBlock (int /*<<< orphan*/ *,void const*,size_t) ; 
 size_t ZSTDv05_decompressSequences (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ ZSTDv05_isError (size_t) ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTDv05_decompressBlock_internal(ZSTDv05_DCtx* dctx,
                            void* dst, size_t dstCapacity,
                      const void* src, size_t srcSize)
{   /* blockType == blockCompressed */
    const BYTE* ip = (const BYTE*)src;
    size_t litCSize;

    if (srcSize >= BLOCKSIZE) return ERROR(srcSize_wrong);

    /* Decode literals sub-block */
    litCSize = ZSTDv05_decodeLiteralsBlock(dctx, src, srcSize);
    if (ZSTDv05_isError(litCSize)) return litCSize;
    ip += litCSize;
    srcSize -= litCSize;

    return ZSTDv05_decompressSequences(dctx, dst, dstCapacity, ip, srcSize);
}