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
struct TYPE_3__ {int* weights; int till_rescale; int tot_weight; int upd_val; int* secondary; int* freqs; int sec_size; int max_upd_val; } ;
typedef  TYPE_1__ Model256 ;

/* Variables and functions */
 int MODEL256_SEC_SCALE ; 

__attribute__((used)) static void model256_update(Model256 *m, int val)
{
    int i, sum = 0;
    unsigned scale;
    int send, sidx = 1;

    m->weights[val]++;
    m->till_rescale--;
    if (m->till_rescale)
        return;
    m->tot_weight += m->upd_val;

    if (m->tot_weight > 0x8000) {
        m->tot_weight = 0;
        for (i = 0; i < 256; i++) {
            m->weights[i]  = (m->weights[i] + 1) >> 1;
            m->tot_weight +=  m->weights[i];
        }
    }
    scale = 0x80000000u / m->tot_weight;
    m->secondary[0] = 0;
    for (i = 0; i < 256; i++) {
        m->freqs[i] = sum * scale >> 16;
        sum += m->weights[i];
        send = m->freqs[i] >> MODEL256_SEC_SCALE;
        while (sidx <= send)
            m->secondary[sidx++] = i - 1;
    }
    while (sidx < m->sec_size)
        m->secondary[sidx++] = 255;

    m->upd_val = m->upd_val * 5 >> 2;
    if (m->upd_val > m->max_upd_val)
        m->upd_val = m->max_upd_val;
    m->till_rescale = m->upd_val;
}