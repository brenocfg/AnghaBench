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
 scalar_t__ CABAC_MASK ; 

__attribute__((used)) static void refill(CABACContext *c){
#if CABAC_BITS == 16
        c->low+= (c->bytestream[0]<<9) + (c->bytestream[1]<<1);
#else
        c->low+= c->bytestream[0]<<1;
#endif
    c->low -= CABAC_MASK;
#if !UNCHECKED_BITSTREAM_READER
    if (c->bytestream < c->bytestream_end)
#endif
        c->bytestream += CABAC_BITS / 8;
}