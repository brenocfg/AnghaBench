#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long long frameContentSize; } ;
typedef  TYPE_1__ ZSTDv07_frameParams ;

/* Variables and functions */
 size_t ZSTDv07_getFrameParams (TYPE_1__*,void const*,size_t) ; 

unsigned long long ZSTDv07_getDecompressedSize(const void* src, size_t srcSize)
{
    ZSTDv07_frameParams fparams;
    size_t const frResult = ZSTDv07_getFrameParams(&fparams, src, srcSize);
    if (frResult!=0) return 0;
    return fparams.frameContentSize;
}