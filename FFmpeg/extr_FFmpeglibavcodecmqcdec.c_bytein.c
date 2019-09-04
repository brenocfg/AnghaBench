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
struct TYPE_3__ {int* bp; scalar_t__ c; } ;
typedef  TYPE_1__ MqcState ;

/* Variables and functions */

__attribute__((used)) static void bytein(MqcState *mqc)
{
    if (*mqc->bp == 0xff) {
        if (*(mqc->bp + 1) > 0x8f)
            mqc->c++;
        else {
            mqc->bp++;
            mqc->c += 2 + 0xfe00 - (*mqc->bp << 9);
        }
    } else {
        mqc->bp++;
        mqc->c += 1 + 0xff00 - (*mqc->bp << 8);
    }
}