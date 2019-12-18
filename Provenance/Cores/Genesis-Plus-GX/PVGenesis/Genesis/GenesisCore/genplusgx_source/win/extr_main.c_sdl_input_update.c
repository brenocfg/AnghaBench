#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_5__ {int w; int h; } ;
struct TYPE_8__ {TYPE_1__ viewport; } ;
struct TYPE_7__ {int /*<<< orphan*/  invert_mouse; } ;
struct TYPE_6__ {int* dev; int** analog; scalar_t__* pad; } ;

/* Variables and functions */
#define  DEVICE_ACTIVATOR 135 
#define  DEVICE_LIGHTGUN 134 
#define  DEVICE_MOUSE 133 
#define  DEVICE_PADDLE 132 
#define  DEVICE_PICO 131 
#define  DEVICE_SPORTSPAD 130 
#define  DEVICE_TEREBI 129 
#define  DEVICE_XE_A1P 128 
 scalar_t__ INPUT_A ; 
 scalar_t__ INPUT_ACTIVATOR_7L ; 
 scalar_t__ INPUT_ACTIVATOR_7U ; 
 scalar_t__ INPUT_ACTIVATOR_8L ; 
 scalar_t__ INPUT_ACTIVATOR_8U ; 
 scalar_t__ INPUT_B ; 
 scalar_t__ INPUT_C ; 
 scalar_t__ INPUT_DOWN ; 
 scalar_t__ INPUT_LEFT ; 
 scalar_t__ INPUT_MODE ; 
 scalar_t__ INPUT_PICO_PEN ; 
 scalar_t__ INPUT_PICO_RED ; 
 scalar_t__ INPUT_RIGHT ; 
 scalar_t__ INPUT_START ; 
 scalar_t__ INPUT_UP ; 
 scalar_t__ INPUT_X ; 
 scalar_t__ INPUT_Y ; 
 scalar_t__ INPUT_Z ; 
 size_t SDLK_DOWN ; 
 size_t SDLK_KP2 ; 
 size_t SDLK_KP4 ; 
 size_t SDLK_KP6 ; 
 size_t SDLK_KP8 ; 
 size_t SDLK_LEFT ; 
 size_t SDLK_RIGHT ; 
 size_t SDLK_UP ; 
 size_t SDLK_a ; 
 size_t SDLK_c ; 
 size_t SDLK_d ; 
 size_t SDLK_f ; 
 size_t SDLK_g ; 
 size_t SDLK_h ; 
 size_t SDLK_j ; 
 size_t SDLK_k ; 
 size_t SDLK_s ; 
 size_t SDLK_v ; 
 size_t SDLK_x ; 
 size_t SDLK_z ; 
 int SDL_BUTTON_LMASK ; 
 int SDL_BUTTON_MMASK ; 
 int SDL_BUTTON_RMASK ; 
 int /*<<< orphan*/ * SDL_GetKeyState (int /*<<< orphan*/ *) ; 
 int SDL_GetMouseState (int*,int*) ; 
 int SDL_GetRelativeMouseState (int*,int*) ; 
 int VIDEO_HEIGHT ; 
 int VIDEO_WIDTH ; 
 TYPE_4__ bitmap ; 
 TYPE_3__ config ; 
 TYPE_2__ input ; 
 size_t joynum ; 
 int pico_current ; 

int sdl_input_update(void)
{
  uint8 *keystate = SDL_GetKeyState(NULL);

  /* reset input */
  input.pad[joynum] = 0;
 
  switch (input.dev[joynum])
  {
    case DEVICE_LIGHTGUN:
    {
      /* get mouse coordinates (absolute values) */
      int x,y;
      int state = SDL_GetMouseState(&x,&y);

      /* X axis */
      input.analog[joynum][0] =  x - (VIDEO_WIDTH-bitmap.viewport.w)/2;

      /* Y axis */
      input.analog[joynum][1] =  y - (VIDEO_HEIGHT-bitmap.viewport.h)/2;

      /* TRIGGER, B, C (Menacer only), START (Menacer & Justifier only) */
      if(state & SDL_BUTTON_LMASK) input.pad[joynum] |= INPUT_A;
      if(state & SDL_BUTTON_RMASK) input.pad[joynum] |= INPUT_B;
      if(state & SDL_BUTTON_MMASK) input.pad[joynum] |= INPUT_C; 
      if(keystate[SDLK_f])  input.pad[joynum] |= INPUT_START;
      break;
    }

    case DEVICE_PADDLE:
    {
      /* get mouse (absolute values) */
      int x;
      int state = SDL_GetMouseState(&x, NULL);

      /* Range is [0;256], 128 being middle position */
      input.analog[joynum][0] = x * 256 /VIDEO_WIDTH;

      /* Button I -> 0 0 0 0 0 0 0 I*/
      if(state & SDL_BUTTON_LMASK) input.pad[joynum] |= INPUT_B;

      break;
    }

    case DEVICE_SPORTSPAD:
    {
      /* get mouse (relative values) */
      int x,y;
      int state = SDL_GetRelativeMouseState(&x,&y);

      /* Range is [0;256] */
      input.analog[joynum][0] = (unsigned char)(-x & 0xFF);
      input.analog[joynum][1] = (unsigned char)(-y & 0xFF);

      /* Buttons I & II -> 0 0 0 0 0 0 II I*/
      if(state & SDL_BUTTON_LMASK) input.pad[joynum] |= INPUT_B;
      if(state & SDL_BUTTON_RMASK) input.pad[joynum] |= INPUT_C;

      break;
    }

    case DEVICE_MOUSE:
    {
      /* get mouse (relative values) */
      int x,y;
      int state = SDL_GetRelativeMouseState(&x,&y);

      /* Sega Mouse range is [-256;+256] */
      input.analog[joynum][0] = x * 2;
      input.analog[joynum][1] = y * 2;

      /* Vertical movement is upsidedown */
      if (!config.invert_mouse)
        input.analog[joynum][1] = 0 - input.analog[joynum][1];

      /* Start,Left,Right,Middle buttons -> 0 0 0 0 START MIDDLE RIGHT LEFT */
      if(state & SDL_BUTTON_LMASK) input.pad[joynum] |= INPUT_B;
      if(state & SDL_BUTTON_RMASK) input.pad[joynum] |= INPUT_C;
      if(state & SDL_BUTTON_MMASK) input.pad[joynum] |= INPUT_A;
      if(keystate[SDLK_f])  input.pad[joynum] |= INPUT_START;

      break;
    }

    case DEVICE_XE_A1P:
    {
      /* A,B,C,D,Select,START,E1,E2 buttons -> E1(?) E2(?) START SELECT(?) A B C D */
      if(keystate[SDLK_a])  input.pad[joynum] |= INPUT_START;
      if(keystate[SDLK_s])  input.pad[joynum] |= INPUT_A;
      if(keystate[SDLK_d])  input.pad[joynum] |= INPUT_C;
      if(keystate[SDLK_f])  input.pad[joynum] |= INPUT_Y;
      if(keystate[SDLK_z])  input.pad[joynum] |= INPUT_B;
      if(keystate[SDLK_x])  input.pad[joynum] |= INPUT_X;
      if(keystate[SDLK_c])  input.pad[joynum] |= INPUT_MODE;
      if(keystate[SDLK_v])  input.pad[joynum] |= INPUT_Z;
      
      /* Left Analog Stick (bidirectional) */
      if(keystate[SDLK_UP])     input.analog[joynum][1]-=2;
      else if(keystate[SDLK_DOWN])   input.analog[joynum][1]+=2;
      else input.analog[joynum][1] = 128;
      if(keystate[SDLK_LEFT])   input.analog[joynum][0]-=2;
      else if(keystate[SDLK_RIGHT])  input.analog[joynum][0]+=2;
      else input.analog[joynum][0] = 128;

      /* Right Analog Stick (unidirectional) */
      if(keystate[SDLK_KP8])    input.analog[joynum+1][0]-=2;
      else if(keystate[SDLK_KP2])   input.analog[joynum+1][0]+=2;
      else if(keystate[SDLK_KP4])   input.analog[joynum+1][0]-=2;
      else if(keystate[SDLK_KP6])  input.analog[joynum+1][0]+=2;
      else input.analog[joynum+1][0] = 128;

      /* Limiters */
      if (input.analog[joynum][0] > 0xFF) input.analog[joynum][0] = 0xFF;
      else if (input.analog[joynum][0] < 0) input.analog[joynum][0] = 0;
      if (input.analog[joynum][1] > 0xFF) input.analog[joynum][1] = 0xFF;
      else if (input.analog[joynum][1] < 0) input.analog[joynum][1] = 0;
      if (input.analog[joynum+1][0] > 0xFF) input.analog[joynum+1][0] = 0xFF;
      else if (input.analog[joynum+1][0] < 0) input.analog[joynum+1][0] = 0;
      if (input.analog[joynum+1][1] > 0xFF) input.analog[joynum+1][1] = 0xFF;
      else if (input.analog[joynum+1][1] < 0) input.analog[joynum+1][1] = 0;

      break;
    }

    case DEVICE_PICO:
    {
      /* get mouse (absolute values) */
      int x,y;
      int state = SDL_GetMouseState(&x,&y);

      /* Calculate X Y axis values */
      input.analog[0][0] = 0x3c  + (x * (0x17c-0x03c+1)) / VIDEO_WIDTH;
      input.analog[0][1] = 0x1fc + (y * (0x2f7-0x1fc+1)) / VIDEO_HEIGHT;
   
      /* Map mouse buttons to player #1 inputs */
      if(state & SDL_BUTTON_MMASK) pico_current = (pico_current + 1) & 7;
      if(state & SDL_BUTTON_RMASK) input.pad[0] |= INPUT_PICO_RED;
      if(state & SDL_BUTTON_LMASK) input.pad[0] |= INPUT_PICO_PEN;

      break;
    }

    case DEVICE_TEREBI:
    {
      /* get mouse (absolute values) */
      int x,y;
      int state = SDL_GetMouseState(&x,&y);

      /* Calculate X Y axis values */
      input.analog[0][0] = (x * 250) / VIDEO_WIDTH;
      input.analog[0][1] = (y * 250) / VIDEO_HEIGHT;
   
      /* Map mouse buttons to player #1 inputs */
      if(state & SDL_BUTTON_RMASK) input.pad[0] |= INPUT_B;

      break;
    }

    case DEVICE_ACTIVATOR:
    {
      if(keystate[SDLK_g])  input.pad[joynum] |= INPUT_ACTIVATOR_7L;
      if(keystate[SDLK_h])  input.pad[joynum] |= INPUT_ACTIVATOR_7U;
      if(keystate[SDLK_j])  input.pad[joynum] |= INPUT_ACTIVATOR_8L;
      if(keystate[SDLK_k])  input.pad[joynum] |= INPUT_ACTIVATOR_8U;
    }

    default:
    {
      if(keystate[SDLK_a])  input.pad[joynum] |= INPUT_A;
      if(keystate[SDLK_s])  input.pad[joynum] |= INPUT_B;
      if(keystate[SDLK_d])  input.pad[joynum] |= INPUT_C;
      if(keystate[SDLK_f])  input.pad[joynum] |= INPUT_START;
      if(keystate[SDLK_z])  input.pad[joynum] |= INPUT_X;
      if(keystate[SDLK_x])  input.pad[joynum] |= INPUT_Y;
      if(keystate[SDLK_c])  input.pad[joynum] |= INPUT_Z;
      if(keystate[SDLK_v])  input.pad[joynum] |= INPUT_MODE;

      if(keystate[SDLK_UP]) input.pad[joynum] |= INPUT_UP;
      else
      if(keystate[SDLK_DOWN]) input.pad[joynum] |= INPUT_DOWN;
      if(keystate[SDLK_LEFT]) input.pad[joynum] |= INPUT_LEFT;
      else
      if(keystate[SDLK_RIGHT]) input.pad[joynum] |= INPUT_RIGHT;

      break;
    }
  }
  return 1;
}