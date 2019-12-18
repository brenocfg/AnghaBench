#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  unsigned int uint32_t ;
struct TYPE_4__ {int error; scalar_t__ eof_reached; } ;
typedef  TYPE_1__ AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  EIO ; 
 int avio_r8 (TYPE_1__*) ; 

__attribute__((used)) static int leb(AVIOContext *pb, uint32_t *len) {
    int more, i = 0;
    uint8_t byte;
    *len = 0;
    do {
        unsigned bits;
        byte = avio_r8(pb);
        more = byte & 0x80;
        bits = byte & 0x7f;
        if (i <= 3 || (i == 4 && bits < (1 << 4)))
            *len |= bits << (i * 7);
        else if (bits)
            return AVERROR_INVALIDDATA;
        if (++i == 8 && more)
            return AVERROR_INVALIDDATA;
        if (pb->eof_reached || pb->error)
            return pb->error ? pb->error : AVERROR(EIO);
    } while (more);
    return i;
}