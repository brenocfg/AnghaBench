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
struct TYPE_3__ {int pos; int val; int* buf; } ;
typedef  TYPE_1__ bitbuf_t ;

/* Variables and functions */
 int* bitmask ; 

__attribute__((used)) static inline unsigned int bits_peek(bitbuf_t *bb, int bits)
{
    unsigned int val;
    int left = 32 - (bb->pos & 31);

    if (bits < left)
    {
        val = (bb->val >> (left - bits)) & bitmask[bits];
    }
    else
    {
        val = (bb->val & bitmask[left]) << (bits - left);
        int bpos = bb->pos + left;
        bits -= left;


        if (bits > 0)
        {
            int pos = bpos >> 3;
            int bval =  (bb->buf[pos]     << 24) |
                        (bb->buf[pos + 1] << 16) |
                        (bb->buf[pos + 2] <<  8) |
                         bb->buf[pos + 3];
            val |= (bval >> (32 - bits)) & bitmask[bits];
        }
    }

    return val;
}