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
struct TYPE_4__ {int a; int /*<<< orphan*/  ct; scalar_t__ c; } ;
typedef  TYPE_1__ MqcState ;

/* Variables and functions */
 int /*<<< orphan*/  byteout (TYPE_1__*) ; 

__attribute__((used)) static void renorme(MqcState *mqc)
{
    do{
        mqc->a += mqc->a;
        mqc->c += mqc->c;
        if (!--mqc->ct)
            byteout(mqc);
    } while (!(mqc->a & 0x8000));
}