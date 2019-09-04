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
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {scalar_t__* bpstart; scalar_t__* bp; } ;
typedef  TYPE_1__ MqcState ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  ff_mqc_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 

int ff_mqc_flush_to(MqcState *mqc, uint8_t *dst, int *dst_len)
{
    MqcState mqc2 = *mqc;
    mqc2.bpstart=
    mqc2.bp = dst;
    *mqc2.bp = *mqc->bp;
    ff_mqc_flush(&mqc2);
    *dst_len = mqc2.bp - dst;
    if (mqc->bp < mqc->bpstart) {
        av_assert1(mqc->bpstart - mqc->bp == 1);
        av_assert1(*dst_len > 0);
        av_assert1(mqc->bp[0] == 0 && dst[0] == 0);
        (*dst_len) --;
        memmove(dst, dst+1, *dst_len);
        return mqc->bp - mqc->bpstart + 1 + *dst_len;
    }
    return mqc->bp - mqc->bpstart + *dst_len;
}