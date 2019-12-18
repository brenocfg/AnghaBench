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
struct TYPE_3__ {int len; int size; scalar_t__* str; } ;
typedef  TYPE_1__ AVBPrint ;

/* Variables and functions */
 size_t FFMIN (unsigned int,int) ; 
 int UINT_MAX ; 

__attribute__((used)) static void av_bprint_grow(AVBPrint *buf, unsigned extra_len)
{
    /* arbitrary margin to avoid small overflows */
    extra_len = FFMIN(extra_len, UINT_MAX - 5 - buf->len);
    buf->len += extra_len;
    if (buf->size)
        buf->str[FFMIN(buf->len, buf->size - 1)] = 0;
}