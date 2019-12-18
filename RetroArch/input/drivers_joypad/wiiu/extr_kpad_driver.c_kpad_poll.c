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
typedef  int /*<<< orphan*/  kpad ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  KPADData ;

/* Variables and functions */
 scalar_t__ KPADRead (unsigned int,int /*<<< orphan*/ *,int) ; 
 unsigned int WIIU_WIIMOTE_CHANNELS ; 
 int /*<<< orphan*/  kpad_deregister (unsigned int) ; 
 int /*<<< orphan*/  kpad_poll_one_channel (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int* poll_failures ; 

__attribute__((used)) static void kpad_poll(void)
{
   unsigned channel;
   KPADData kpad;
   int32_t result = 0;

   for (channel = 0; channel < WIIU_WIIMOTE_CHANNELS; channel++)
   {
      memset(&kpad, 0, sizeof(kpad));

      result = KPADRead(channel, &kpad, 1);
      /* this is a hack to prevent spurious disconnects */
      /* TODO: use KPADSetConnectCallback and use callbacks to detect */
      /*       pad disconnects properly. */
      if (result == 0)
      {
         poll_failures[channel]++;
         if(poll_failures[channel] > 5)
            kpad_deregister(channel);
         continue;
      }
      poll_failures[channel] = 0;

      kpad_poll_one_channel(channel, &kpad);
   }
}