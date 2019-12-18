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
struct TYPE_2__ {int* map; scalar_t__* setup; } ;

/* Variables and functions */
 int MAX_LEDS ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int,int,int) ; 
 int /*<<< orphan*/  RARCH_WARN (char*,int,...) ; 
 TYPE_1__* cur ; 
 int /*<<< orphan*/  set_gpio (int,int) ; 
 scalar_t__ setup_gpio (int) ; 

__attribute__((used)) static void rpi_set(int led, int state)
{
   int gpio = 0;

   if((led < 0) || (led >= MAX_LEDS))
   {
      RARCH_WARN("[LED]: invalid led %d\n", led);
      return;
   }

   gpio = cur->map[led];
   if(gpio <= 0)
      return;

   if(cur->setup[led] == 0)
   {
      RARCH_LOG("[LED]: rpi setup led %d gpio %d\n",
            led, gpio, state);
      cur->setup[led] = setup_gpio(gpio);
      if(cur->setup[led] <= 0)
      {
         RARCH_WARN("[LED]: failed to setup led %d gpio %d\n",
               led, gpio);
      }
   }
   if(cur->setup[led] > 0)
   {
      RARCH_LOG("[LED]: rpi LED driver set led %d gpio %d = %d\n",
            led, gpio, state);
      set_gpio(gpio, state);
   }
}