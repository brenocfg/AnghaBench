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

/* Variables and functions */
 unsigned char* characters ; 
 int /*<<< orphan*/  dbprintf (int,char*,unsigned char,unsigned char,scalar_t__,unsigned char,unsigned char,unsigned char) ; 
 scalar_t__* lo_base ; 
 unsigned char* lo_offset ; 
 int /*<<< orphan*/  zassert (int,int,char*,int,unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static inline signed char decode_lo (int sig)
{
    unsigned char offset = (((sig >> 1) & 0x01) |
                            ((sig >> 3) & 0x06) |
                            ((sig >> 5) & 0x18) |
                            ((sig >> 7) & 0x60));
    unsigned char idx = lo_offset[offset];
    unsigned char base, c;

    if(sig & 1)
        idx &= 0xf;
    else
        idx >>= 4;
    if(idx == 0xf)
        return(-1);

    base = (sig >> 11) | ((sig >> 9) & 1);
    zassert(base < 8, -1, "sig=%x offset=%x idx=%x base=%x\n",
            sig, offset, idx, base);
    idx += lo_base[base];

    zassert(idx <= 0x50, -1, "sig=%x offset=%x base=%x idx=%x\n",
            sig, offset, base, idx);
    c = characters[idx];
    dbprintf(2, " %02x(%x(%02x)/%x(%02x)) => %02x",
             idx, base, lo_base[base], offset, lo_offset[offset],
             (unsigned char)c);
    return(c);
}