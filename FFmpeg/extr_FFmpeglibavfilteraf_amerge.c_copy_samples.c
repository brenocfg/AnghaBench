#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct amerge_input {int nb_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void copy_samples(int nb_inputs, struct amerge_input in[],
                                int *route, uint8_t *ins[],
                                uint8_t **outs, int ns, int bps)
{
    int *route_cur;
    int i, c, nb_ch = 0;

    for (i = 0; i < nb_inputs; i++)
        nb_ch += in[i].nb_ch;
    while (ns--) {
        route_cur = route;
        for (i = 0; i < nb_inputs; i++) {
            for (c = 0; c < in[i].nb_ch; c++) {
                memcpy((*outs) + bps * *(route_cur++), ins[i], bps);
                ins[i] += bps;
            }
        }
        *outs += nb_ch * bps;
    }
}