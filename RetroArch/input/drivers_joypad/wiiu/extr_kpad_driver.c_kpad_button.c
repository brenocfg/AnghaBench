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
typedef  int uint16_t ;
struct TYPE_2__ {int button_state; } ;

/* Variables and functions */
 int UINT64_C (int) ; 
 int /*<<< orphan*/  kpad_query_pad (unsigned int) ; 
 int to_wiimote_channel (unsigned int) ; 
 TYPE_1__* wiimotes ; 

__attribute__((used)) static bool kpad_button(unsigned pad, uint16_t button_bit)
{
   int channel;
   if (!kpad_query_pad(pad))
      return false;

   channel = to_wiimote_channel(pad);
   if(channel < 0)
      return false;

   return wiimotes[channel].button_state
      & (UINT64_C(1) << button_bit);
}