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
typedef  size_t uint8_t ;
struct TYPE_4__ {int a; int c; } ;
typedef  TYPE_1__ MqcState ;

/* Variables and functions */
 size_t* ff_mqc_nlps ; 
 size_t* ff_mqc_nmps ; 
 int* ff_mqc_qe ; 
 int /*<<< orphan*/  renorme (TYPE_1__*) ; 

void ff_mqc_encode(MqcState *mqc, uint8_t *cxstate, int d)
{
    int qe;

    qe = ff_mqc_qe[*cxstate];
    mqc->a -= qe;
    if ((*cxstate & 1) == d){
        if (!(mqc->a & 0x8000)){
            if (mqc->a < qe)
                mqc->a = qe;
            else
                mqc->c += qe;
            *cxstate = ff_mqc_nmps[*cxstate];
            renorme(mqc);
        } else
            mqc->c += qe;
    } else{
        if (mqc->a < qe)
            mqc->c += qe;
        else
            mqc->a = qe;
        *cxstate = ff_mqc_nlps[*cxstate];
        renorme(mqc);
    }
}