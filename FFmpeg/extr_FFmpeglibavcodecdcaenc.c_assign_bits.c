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
struct TYPE_4__ {int worst_quantization_noise; scalar_t__ consumed_bits; scalar_t__ frame_bits; int worst_noise_ever; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */
 int USED_1ABITS ; 
 int USED_26ABITS ; 
 int init_quantization_noise (TYPE_1__*,int,int) ; 
 int snr_fudge ; 

__attribute__((used)) static void assign_bits(DCAEncContext *c)
{
    /* Find the bounds where the binary search should work */
    int low, high, down;
    int used_abits = 0;
    int forbid_zero = 1;
restart:
    init_quantization_noise(c, c->worst_quantization_noise, forbid_zero);
    low = high = c->worst_quantization_noise;
    if (c->consumed_bits > c->frame_bits) {
        while (c->consumed_bits > c->frame_bits) {
            if (used_abits == USED_1ABITS && forbid_zero) {
                forbid_zero = 0;
                goto restart;
            }
            low = high;
            high += snr_fudge;
            used_abits = init_quantization_noise(c, high, forbid_zero);
        }
    } else {
        while (c->consumed_bits <= c->frame_bits) {
            high = low;
            if (used_abits == USED_26ABITS)
                goto out; /* The requested bitrate is too high, pad with zeros */
            low -= snr_fudge;
            used_abits = init_quantization_noise(c, low, forbid_zero);
        }
    }

    /* Now do a binary search between low and high to see what fits */
    for (down = snr_fudge >> 1; down; down >>= 1) {
        init_quantization_noise(c, high - down, forbid_zero);
        if (c->consumed_bits <= c->frame_bits)
            high -= down;
    }
    init_quantization_noise(c, high, forbid_zero);
out:
    c->worst_quantization_noise = high;
    if (high > c->worst_noise_ever)
        c->worst_noise_ever = high;
}