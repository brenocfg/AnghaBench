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
struct TYPE_3__ {int zero_weight; int till_rescale; int total_weight; int upd_val; unsigned int zero_freq; unsigned int total_freq; } ;
typedef  TYPE_1__ Model2 ;

/* Variables and functions */

__attribute__((used)) static void model2_update(Model2 *m, int bit)
{
    unsigned scale;

    if (!bit)
        m->zero_weight++;
    m->till_rescale--;
    if (m->till_rescale)
        return;

    m->total_weight += m->upd_val;
    if (m->total_weight > 0x2000) {
        m->total_weight = (m->total_weight + 1) >> 1;
        m->zero_weight  = (m->zero_weight  + 1) >> 1;
        if (m->total_weight == m->zero_weight)
            m->total_weight = m->zero_weight + 1;
    }
    m->upd_val = m->upd_val * 5 >> 2;
    if (m->upd_val > 64)
        m->upd_val = 64;
    scale = 0x80000000u / m->total_weight;
    m->zero_freq    = m->zero_weight  * scale >> 18;
    m->total_freq   = m->total_weight * scale >> 18;
    m->till_rescale = m->upd_val;
}