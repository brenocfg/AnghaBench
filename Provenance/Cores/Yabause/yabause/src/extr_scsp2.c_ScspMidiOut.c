#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int midi_out_cnt; int mofull; int /*<<< orphan*/ * midi_out_buf; scalar_t__ moemp; } ;

/* Variables and functions */
 TYPE_1__ scsp ; 

__attribute__((used)) static void ScspMidiOut(u8 data)
{
   scsp.moemp = 0;
   if (scsp.midi_out_cnt < 4)
      scsp.midi_out_buf[scsp.midi_out_cnt++] = data;
   scsp.mofull = (scsp.midi_out_cnt >= 4);
}