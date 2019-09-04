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
struct TYPE_4__ {int c; } ;
typedef  TYPE_1__ MqcState ;

/* Variables and functions */
 int /*<<< orphan*/  bytein (TYPE_1__*) ; 

__attribute__((used)) static int mqc_decode_bypass(MqcState *mqc) {
    int bit = !(mqc->c & 0x40000000);
    if (!(mqc->c & 0xff)) {
        mqc->c -= 0x100;
        bytein(mqc);
    }
    mqc->c += mqc->c;
    return bit;
}