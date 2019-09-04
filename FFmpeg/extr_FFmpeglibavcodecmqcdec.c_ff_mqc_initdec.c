#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int raw; int* bp; int c; int a; } ;
typedef  TYPE_1__ MqcState ;

/* Variables and functions */
 int /*<<< orphan*/  bytein (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_mqc_init_contexts (TYPE_1__*) ; 

void ff_mqc_initdec(MqcState *mqc, uint8_t *bp, int raw, int reset)
{
    mqc->raw = raw;
    if (reset)
        ff_mqc_init_contexts(mqc);
    mqc->bp = bp;
    mqc->c  = (*mqc->bp ^ 0xff) << 16;
    bytein(mqc);
    mqc->c = mqc->c << 7;
    mqc->a = 0x8000;
}