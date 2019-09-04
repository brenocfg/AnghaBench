#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/ * payload; } ;
struct TYPE_4__ {TYPE_1__ s; } ;

/* Variables and functions */
 TYPE_2__* ledpackets ; 
 int* panelLEDmap ; 

void globalSet8bit(int index, uint8_t value) {
    int global_row = index / 3 / 14;
    int global_column = (index / 3) % 14;
    int channel = index % 3;
    int panel_row = global_row % 7;
    int panel_column = global_column % 7;
    int panel_index = (global_row / 7)*2+(global_column / 7);
    int addr = panelLEDmap[(panel_row*7+panel_column)*3+channel];
    addr += (addr>>5)*16;   // make sure things are in the correct places for the 5 LED board CPUs to find them
    ledpackets[panel_index].s.payload[addr] = value;
}