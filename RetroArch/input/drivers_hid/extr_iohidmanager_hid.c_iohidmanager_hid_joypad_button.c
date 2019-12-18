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
struct TYPE_2__ {int* buttons; int /*<<< orphan*/ ** hats; } ;
typedef  TYPE_1__ iohidmanager_hid_t ;
typedef  int /*<<< orphan*/  input_bits_t ;

/* Variables and functions */
 scalar_t__ BIT256_GET (int /*<<< orphan*/ ,int) ; 
 unsigned int GET_HAT (int) ; 
 unsigned int GET_HAT_DIR (int) ; 
#define  HAT_DOWN_MASK 131 
#define  HAT_LEFT_MASK 130 
#define  HAT_RIGHT_MASK 129 
#define  HAT_UP_MASK 128 
 unsigned int MAX_USERS ; 
 int /*<<< orphan*/  iohidmanager_hid_joypad_get_buttons (void*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool iohidmanager_hid_joypad_button(void *data,
      unsigned port, uint16_t joykey)
{
  input_bits_t buttons;
  iohidmanager_hid_t *hid   = (iohidmanager_hid_t*)data;
  unsigned hat_dir = GET_HAT_DIR(joykey);

  iohidmanager_hid_joypad_get_buttons(data, port, &buttons);

   /* Check hat. */
   if (hat_dir)
   {
      unsigned h = GET_HAT(joykey);
      if (h >= 1)
         return false;

      switch(hat_dir)
      {
         case HAT_LEFT_MASK:
            return hid->hats[port][0] < 0;
         case HAT_RIGHT_MASK:
            return hid->hats[port][0] > 0;
         case HAT_UP_MASK:
            return hid->hats[port][1] < 0;
         case HAT_DOWN_MASK:
            return hid->hats[port][1] > 0;
      }

      return 0;
   }

   /* Check the button. */
   if ((port < MAX_USERS) && (joykey < 32))
      return (BIT256_GET(buttons, joykey) != 0)
         || ((hid->buttons[port] & (1 << joykey)) != 0);

   return false;
}