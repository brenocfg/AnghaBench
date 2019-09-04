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
struct TYPE_4__ {int* weights; int upd_val; int till_rescale; scalar_t__ tot_weight; } ;
typedef  TYPE_1__ Model256 ;

/* Variables and functions */
 int /*<<< orphan*/  model256_update (TYPE_1__*,int) ; 

__attribute__((used)) static void model256_reset(Model256 *m)
{
    int i;

    for (i = 0; i < 255; i++)
        m->weights[i] = 1;
    m->weights[255] = 0;

    m->tot_weight   = 0;
    m->upd_val      = 256;
    m->till_rescale = 1;
    model256_update(m, 255);
    m->till_rescale =
    m->upd_val      = (256 + 6) >> 1;
}