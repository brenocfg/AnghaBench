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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  input_bits_t ;

/* Variables and functions */
 scalar_t__ BIT256_GET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ GET_HAT_DIR (int) ; 
 unsigned int MAX_USERS ; 
 int /*<<< orphan*/  wiiusb_hid_joypad_get_buttons (void*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool wiiusb_hid_joypad_button(void *data,
      unsigned port, uint16_t joykey)
{
  input_bits_t buttons;

  wiiusb_hid_joypad_get_buttons(data, port, &buttons);

  /* Check hat. */
  if (GET_HAT_DIR(joykey))
    return false;

  /* Check the button. */
  if ((port < MAX_USERS) && (joykey < 32))
    return (BIT256_GET(buttons, joykey) != 0);

  return false;
}