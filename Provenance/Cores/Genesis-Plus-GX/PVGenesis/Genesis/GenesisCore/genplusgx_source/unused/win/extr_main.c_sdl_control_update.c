#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_10__ {int member_0; int member_1; } ;
typedef  TYPE_2__ uint16 ;
struct TYPE_9__ {int changed; } ;
struct TYPE_15__ {TYPE_1__ viewport; } ;
struct TYPE_14__ {int render; int overscan; } ;
struct TYPE_13__ {int /*<<< orphan*/ * dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  surf_screen; } ;
struct TYPE_11__ {int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  sample_rate; } ;
typedef  int SDLKey ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t MAX_DEVICES ; 
 int /*<<< orphan*/  NO_DEVICE ; 
#define  SDLK_ESCAPE 140 
#define  SDLK_F10 139 
#define  SDLK_F11 138 
#define  SDLK_F12 137 
#define  SDLK_F2 136 
#define  SDLK_F3 135 
#define  SDLK_F4 134 
#define  SDLK_F5 133 
#define  SDLK_F6 132 
#define  SDLK_F7 131 
#define  SDLK_F8 130 
#define  SDLK_F9 129 
#define  SDLK_TAB 128 
 int SDL_FULLSCREEN ; 
 int SDL_SWSURFACE ; 
 int /*<<< orphan*/  SDL_SetVideoMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int STATE_SIZE ; 
 int /*<<< orphan*/  VIDEO_HEIGHT ; 
 int /*<<< orphan*/  VIDEO_WIDTH ; 
 int /*<<< orphan*/  YM2612GetContextPtr () ; 
 int /*<<< orphan*/  YM2612GetContextSize () ; 
 int /*<<< orphan*/  YM2612Restore (unsigned char*) ; 
 int /*<<< orphan*/  audio_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__ bitmap ; 
 TYPE_7__ config ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int fullscreen ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_softreset (int) ; 
 TYPE_6__ input ; 
 size_t joynum ; 
 int log_error ; 
 unsigned char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* reg ; 
 TYPE_5__ sdl_video ; 
 TYPE_4__ snd ; 
 int /*<<< orphan*/  state_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  state_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_init () ; 
 int /*<<< orphan*/  system_reset () ; 
 int turbo_mode ; 
 int use_sound ; 
 TYPE_2__ vc_max ; 
 int vdp_pal ; 

__attribute__((used)) static int sdl_control_update(SDLKey keystate)
{
    switch (keystate)
    {
      case SDLK_TAB:
      {
        system_init();
        system_reset();
        break;
      }

      case SDLK_F2:
      {
        if (fullscreen) fullscreen = 0;
        else fullscreen = SDL_FULLSCREEN;
        sdl_video.surf_screen = SDL_SetVideoMode(VIDEO_WIDTH, VIDEO_HEIGHT, 16,  SDL_SWSURFACE | fullscreen);
        break;
      }

      case SDLK_F3:
      {
        config.render ^=1;
        break;
      }

      case SDLK_F4:
      {
        if (!turbo_mode) use_sound ^= 1;
        break;
      }

      case SDLK_F5:
      {
        log_error ^= 1;
        break;
      }

      case SDLK_F6:
      {
        if (!use_sound) turbo_mode ^=1;
        break;
      }

      case SDLK_F7:
      {
        FILE *f = fopen("game.gpz","r+b");
        if (f)
        {
          uint8 buf[STATE_SIZE];
          fread(&buf, STATE_SIZE, 1, f);
          state_load(buf);
          fclose(f);
        }
        break;
      }

      case SDLK_F8:
      {
        FILE *f = fopen("game.gpz","w+b");
        if (f)
        {
          uint8 buf[STATE_SIZE];
          state_save(buf);
          fwrite(&buf, STATE_SIZE, 1, f);
          fclose(f);
        }
        break;
      }

      case SDLK_F9:
      {
        vdp_pal ^= 1;

        /* save YM2612 context */
        unsigned char *temp = malloc(YM2612GetContextSize());
        if (temp)
          memcpy(temp, YM2612GetContextPtr(), YM2612GetContextSize());

        /* reinitialize all timings */
        audio_init(snd.sample_rate, snd.frame_rate);
        system_init();

        /* restore YM2612 context */
        if (temp)
        {
          YM2612Restore(temp);
          free(temp);
        }
        
        /* reinitialize VC max value */
        static const uint16 vc_table[4][2] = 
        {
          /* NTSC, PAL */
          {0xDA , 0xF2},  /* Mode 4 (192 lines) */
          {0xEA , 0x102}, /* Mode 5 (224 lines) */
          {0xDA , 0xF2},  /* Mode 4 (192 lines) */
          {0x106, 0x10A}  /* Mode 5 (240 lines) */
        };
        vc_max = vc_table[(reg[1] >> 2) & 3][vdp_pal];

        /* reinitialize display area */
        bitmap.viewport.changed = 3;
        break;
      }

      case SDLK_F10:
      {
        gen_softreset(1);
        gen_softreset(0);
        break;
      }

      case SDLK_F11:
      {
        config.overscan ^= 1;
        bitmap.viewport.changed = 3;
        break;
      }

      case SDLK_F12:
      {
        joynum = (joynum + 1) % MAX_DEVICES;
        while (input.dev[joynum] == NO_DEVICE)
        {
          joynum = (joynum + 1) % MAX_DEVICES;
        }
        break;
      }

      case SDLK_ESCAPE:
      {
        return 0;
      }

      default:
        break;
    }

   return 1;
}