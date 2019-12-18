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
struct retro_keybind {unsigned int mbutton; unsigned int joykey; void* joyaxis; } ;
struct menu_bind_state_port {scalar_t__* axes; int* hats; scalar_t__* buttons; scalar_t__* mbuttons; } ;
struct menu_bind_state {TYPE_1__* axis_state; int /*<<< orphan*/ * state; } ;
struct TYPE_2__ {int* locked_axes; scalar_t__* rested_axes; } ;

/* Variables and functions */
 void* AXIS_NEG (unsigned int) ; 
 void* AXIS_NONE ; 
 void* AXIS_POS (unsigned int) ; 
 int HAT_DOWN_MASK ; 
 int HAT_LEFT_MASK ; 
 unsigned int HAT_MAP (unsigned int,int) ; 
 int HAT_RIGHT_MASK ; 
 int HAT_UP_MASK ; 
 unsigned int MENU_MAX_AXES ; 
 unsigned int MENU_MAX_BUTTONS ; 
 unsigned int MENU_MAX_HATS ; 
 unsigned int MENU_MAX_MBUTTONS ; 
 unsigned int NO_BTN ; 
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_4 136 
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_5 135 
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN 134 
#define  RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP 133 
#define  RETRO_DEVICE_ID_MOUSE_LEFT 132 
#define  RETRO_DEVICE_ID_MOUSE_MIDDLE 131 
#define  RETRO_DEVICE_ID_MOUSE_RIGHT 130 
#define  RETRO_DEVICE_ID_MOUSE_WHEELDOWN 129 
#define  RETRO_DEVICE_ID_MOUSE_WHEELUP 128 
 int abs (scalar_t__) ; 

__attribute__((used)) static bool menu_input_key_bind_poll_find_trigger_pad(
      struct menu_bind_state *state,
      struct menu_bind_state *new_state,
     struct retro_keybind * output,
      unsigned p)
{
   unsigned a, b, h;
   const struct menu_bind_state_port *n = (const struct menu_bind_state_port*)
      &new_state->state[p];
   const struct menu_bind_state_port *o = (const struct menu_bind_state_port*)
      &state->state[p];

   for (b = 0; b < MENU_MAX_MBUTTONS; b++)
   {
      bool iterate = n->mbuttons[b] && !o->mbuttons[b];

      if (!iterate)
         continue;

      switch ( b )
      {

     case RETRO_DEVICE_ID_MOUSE_LEFT:
     case RETRO_DEVICE_ID_MOUSE_RIGHT:
     case RETRO_DEVICE_ID_MOUSE_MIDDLE:
     case RETRO_DEVICE_ID_MOUSE_BUTTON_4:
     case RETRO_DEVICE_ID_MOUSE_BUTTON_5:
     case RETRO_DEVICE_ID_MOUSE_WHEELUP:
     case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
     case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELUP:
     case RETRO_DEVICE_ID_MOUSE_HORIZ_WHEELDOWN:
        output->mbutton = b;
        return true;
     }
   }

   for (b = 0; b < MENU_MAX_BUTTONS; b++)
   {
      bool iterate = n->buttons[b] && !o->buttons[b];

      if (!iterate)
         continue;

      output->joykey = b;
      output->joyaxis = AXIS_NONE;
      return true;
   }

   /* Axes are a bit tricky ... */
   for (a = 0; a < MENU_MAX_AXES; a++)
   {
      int locked_distance = abs(n->axes[a] -
            new_state->axis_state[p].locked_axes[a]);
      int rested_distance = abs(n->axes[a] -
            new_state->axis_state[p].rested_axes[a]);

      if (abs(n->axes[a]) >= 20000 &&
            locked_distance >= 20000 &&
            rested_distance >= 20000)
      {
         /* Take care of case where axis rests on +/- 0x7fff
          * (e.g. 360 controller on Linux) */
         output->joyaxis = n->axes[a] > 0
            ? AXIS_POS(a) : AXIS_NEG(a);
         output->joykey = NO_BTN;

         /* Lock the current axis */
         new_state->axis_state[p].locked_axes[a] =
            n->axes[a] > 0 ?
            0x7fff : -0x7fff;
         return true;
      }

      if (locked_distance >= 20000) /* Unlock the axis. */
         new_state->axis_state[p].locked_axes[a] = 0;
   }

   for (h = 0; h < MENU_MAX_HATS; h++)
   {
      uint16_t      trigged = n->hats[h] & (~o->hats[h]);
      uint16_t sane_trigger = 0;

      if (trigged & HAT_UP_MASK)
         sane_trigger = HAT_UP_MASK;
      else if (trigged & HAT_DOWN_MASK)
         sane_trigger = HAT_DOWN_MASK;
      else if (trigged & HAT_LEFT_MASK)
         sane_trigger = HAT_LEFT_MASK;
      else if (trigged & HAT_RIGHT_MASK)
         sane_trigger = HAT_RIGHT_MASK;

      if (sane_trigger)
      {
         output->joykey = HAT_MAP(h, sane_trigger);
         output->joyaxis = AXIS_NONE;
         return true;
      }
   }

   return false;
}