#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int windowLog; } ;
struct TYPE_4__ {size_t headerSize; TYPE_2__ params; } ;
typedef  TYPE_1__ ZSTD_DCtx ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_32bits () ; 
 size_t ZSTD_getFrameParams (TYPE_2__*,void const*,size_t) ; 
 int /*<<< orphan*/  frameParameter_unsupported ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTD_decodeFrameHeader_Part2(ZSTD_DCtx* zc, const void* src, size_t srcSize)
{
    size_t result;
    if (srcSize != zc->headerSize) return ERROR(srcSize_wrong);
    result = ZSTD_getFrameParams(&(zc->params), src, srcSize);
    if ((MEM_32bits()) && (zc->params.windowLog > 25)) return ERROR(frameParameter_unsupported);
    return result;
}