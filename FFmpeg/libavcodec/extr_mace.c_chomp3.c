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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int16_t ;
struct TYPE_4__ {int level; } ;
typedef  TYPE_1__ ChannelData ;

/* Variables and functions */
 int QT_8S_2_16S (int) ; 
 int mace_broken_clip_int16 (int) ; 
 int read_table (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void chomp3(ChannelData *chd, int16_t *output, uint8_t val, int tab_idx)
{

    int16_t current = read_table(chd, val, tab_idx);

    current = mace_broken_clip_int16(current + chd->level);

    chd->level = current - (current >> 3);
    *output = QT_8S_2_16S(current);
}