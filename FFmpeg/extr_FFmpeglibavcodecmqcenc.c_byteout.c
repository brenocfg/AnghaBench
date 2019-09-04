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
struct TYPE_3__ {int* bp; int c; int ct; } ;
typedef  TYPE_1__ MqcState ;

/* Variables and functions */

__attribute__((used)) static void byteout(MqcState *mqc)
{
retry:
    if (*mqc->bp == 0xff){
        mqc->bp++;
        *mqc->bp = mqc->c >> 20;
        mqc->c &= 0xfffff;
        mqc->ct = 7;
    } else if ((mqc->c & 0x8000000)){
        (*mqc->bp)++;
        mqc->c &= 0x7ffffff;
        goto retry;
    } else{
        mqc->bp++;
        *mqc->bp = mqc->c >> 19;
        mqc->c &= 0x7ffff;
        mqc->ct = 8;
    }
}