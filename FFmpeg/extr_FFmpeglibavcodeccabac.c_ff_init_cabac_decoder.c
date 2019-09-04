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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int low; int range; int /*<<< orphan*/  const* bytestream; int /*<<< orphan*/  const* bytestream_end; int /*<<< orphan*/  const* bytestream_start; } ;
typedef  TYPE_1__ CABACContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int CABAC_BITS ; 

int ff_init_cabac_decoder(CABACContext *c, const uint8_t *buf, int buf_size){
    c->bytestream_start=
    c->bytestream= buf;
    c->bytestream_end= buf + buf_size;

#if CABAC_BITS == 16
    c->low =  (*c->bytestream++)<<18;
    c->low+=  (*c->bytestream++)<<10;
    // Keep our fetches on a 2-byte boundary as this should avoid ever having to
    // do unaligned loads if the compiler (or asm) optimises the double byte
    // load into a single instruction
    if(((uintptr_t)c->bytestream & 1) == 0) {
        c->low += (1 << 9);
    }
    else {
        c->low += ((*c->bytestream++) << 2) + 2;
    }
#else
    c->low =  (*c->bytestream++)<<10;
    c->low+= ((*c->bytestream++)<<2) + 2;
#endif
    c->range= 0x1FE;
    if ((c->range<<(CABAC_BITS+1)) < c->low)
        return AVERROR_INVALIDDATA;
    return 0;
}