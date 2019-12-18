#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_5__ {int stride; int* tab1; scalar_t__* tab2; } ;
struct TYPE_4__ {int index; } ;
typedef  TYPE_1__ ChannelData ;

/* Variables and functions */
 TYPE_2__* tabs ; 

__attribute__((used)) static int16_t read_table(ChannelData *chd, uint8_t val, int tab_idx)
{
    int16_t current;

    if (val < tabs[tab_idx].stride)
        current = tabs[tab_idx].tab2[((chd->index & 0x7f0) >> 4) * tabs[tab_idx].stride + val];
    else
        current = - 1 - tabs[tab_idx].tab2[((chd->index & 0x7f0) >> 4)*tabs[tab_idx].stride + 2*tabs[tab_idx].stride-val-1];

    if (( chd->index += tabs[tab_idx].tab1[val]-(chd->index >> 5) ) < 0)
      chd->index = 0;

    return current;
}