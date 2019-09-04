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
struct TYPE_3__ {int low; int* bytestream; int* bytestream_end; } ;
typedef  TYPE_1__ CABACContext ;

/* Variables and functions */
 int CABAC_BITS ; 
 unsigned int CABAC_MASK ; 
 int* ff_h264_norm_shift ; 

__attribute__((used)) static void refill2(CABACContext *c){
    int i;
    unsigned x;
#if !HAVE_FAST_CLZ
    x= c->low ^ (c->low-1);
    i= 7 - ff_h264_norm_shift[x>>(CABAC_BITS-1)];
#else
    i = ff_ctz(c->low) - CABAC_BITS;
#endif

    x= -CABAC_MASK;

#if CABAC_BITS == 16
        x+= (c->bytestream[0]<<9) + (c->bytestream[1]<<1);
#else
        x+= c->bytestream[0]<<1;
#endif

    c->low += x<<i;
#if !UNCHECKED_BITSTREAM_READER
    if (c->bytestream < c->bytestream_end)
#endif
        c->bytestream += CABAC_BITS/8;
}