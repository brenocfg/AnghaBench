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
typedef  int uint8_t ;
struct TYPE_4__ {int* quant; } ;
struct TYPE_5__ {int y; int code_size; TYPE_1__ tbls; } ;
typedef  TYPE_2__ G726Context ;

/* Variables and functions */
 int INT_MAX ; 
 int av_log2_16bit (int) ; 

__attribute__((used)) static inline uint8_t quant(G726Context* c, int d)
{
    int sign, exp, i, dln;

    sign = i = 0;
    if (d < 0) {
        sign = 1;
        d = -d;
    }
    exp = av_log2_16bit(d);
    dln = ((exp<<7) + (((d<<7)>>exp)&0x7f)) - (c->y>>2);

    while (c->tbls.quant[i] < INT_MAX && c->tbls.quant[i] < dln)
        ++i;

    if (sign)
        i = ~i;
    if (c->code_size != 2 && i == 0) /* I'm not sure this is a good idea */
        i = 0xff;

    return i;
}