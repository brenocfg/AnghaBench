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
struct TYPE_4__ {int a; int* bp; int* bpstart; int ct; scalar_t__ c; } ;
typedef  TYPE_1__ MqcState ;

/* Variables and functions */
 int /*<<< orphan*/  ff_mqc_init_contexts (TYPE_1__*) ; 

void ff_mqc_initenc(MqcState *mqc, uint8_t *bp)
{
    ff_mqc_init_contexts(mqc);
    mqc->a = 0x8000;
    mqc->c = 0;
    mqc->bp = bp-1;
    mqc->bpstart = bp;
    mqc->ct = 12 + (*mqc->bp == 0xff);
}