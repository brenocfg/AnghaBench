#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_8__ {int x; int changed; int /*<<< orphan*/  h; } ;
struct TYPE_14__ {TYPE_1__ viewport; } ;
struct TYPE_13__ {int bios; int region_detect; int overscan; int /*<<< orphan*/  gg_extra; } ;
struct TYPE_12__ {int /*<<< orphan*/ * dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  ticks; } ;
struct TYPE_10__ {int /*<<< orphan*/  surf_screen; } ;
struct TYPE_9__ {int /*<<< orphan*/  sample_rate; } ;
typedef  int SDLKey ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t MAX_DEVICES ; 
 int /*<<< orphan*/  NO_DEVICE ; 
#define  SDLK_ESCAPE 141 
#define  SDLK_F1 140 
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
 int /*<<< orphan*/  SDL_ShowCursor (int) ; 
 int STATE_SIZE ; 
 int SYSTEM_GG ; 
 int SYSTEM_MCD ; 
 int SYSTEM_MD ; 
 int SYSTEM_SMS ; 
 int /*<<< orphan*/  VIDEO_HEIGHT ; 
 int /*<<< orphan*/  VIDEO_WIDTH ; 
 int /*<<< orphan*/  audio_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ bitmap ; 
 TYPE_6__ config ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ *) ; 
 int fullscreen ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_region (int /*<<< orphan*/ ) ; 
 TYPE_5__ input ; 
 int* io_reg ; 
 size_t joynum ; 
 int lines_per_frame ; 
 int log_error ; 
 int region_code ; 
 TYPE_4__ sdl_sync ; 
 TYPE_3__ sdl_video ; 
 TYPE_2__ snd ; 
 int /*<<< orphan*/  state_load (int /*<<< orphan*/ *) ; 
 int state_save (int /*<<< orphan*/ *) ; 
 int status ; 
 int system_hw ; 
 int /*<<< orphan*/  system_init () ; 
 int /*<<< orphan*/  system_reset () ; 
 int turbo_mode ; 
 int use_sound ; 
 int /*<<< orphan*/  vc_max ; 
 int /*<<< orphan*/ ** vc_table ; 
 size_t vdp_pal ; 

__attribute__((used)) static int sdl_control_update(SDLKey keystate)
{
    switch (keystate)
    {
      case SDLK_TAB:
      {
        system_reset();
        break;
      }

      case SDLK_F1:
      {
        if (SDL_ShowCursor(-1)) SDL_ShowCursor(0);
        else SDL_ShowCursor(1);
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
        if (config.bios == 0) config.bios = 3;
        else if (config.bios == 3) config.bios = 1;
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
        if (!use_sound)
        {
          turbo_mode ^=1;
          sdl_sync.ticks = 0;
        }
        break;
      }

      case SDLK_F7:
      {
        FILE *f = fopen("game.gp0","rb");
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
        FILE *f = fopen("game.gp0","wb");
        if (f)
        {
          uint8 buf[STATE_SIZE];
          int len = state_save(buf);
          fwrite(&buf, len, 1, f);
          fclose(f);
        }
        break;
      }

      case SDLK_F9:
      {
        config.region_detect = (config.region_detect + 1) % 5;
        get_region(0);

        /* framerate has changed, reinitialize audio timings */
        audio_init(snd.sample_rate, 0);

        /* system with region BIOS should be reinitialized */
        if ((system_hw == SYSTEM_MCD) || ((system_hw & SYSTEM_SMS) && (config.bios & 1)))
        {
          system_init();
          system_reset();
        }
        else
        {
          /* reinitialize I/O region register */
          if (system_hw == SYSTEM_MD)
          {
            io_reg[0x00] = 0x20 | region_code | (config.bios & 1);
          }
          else
          {
            io_reg[0x00] = 0x80 | (region_code >> 1);
          }

          /* reinitialize VDP */
          if (vdp_pal)
          {
            status |= 1;
            lines_per_frame = 313;
          }
          else
          {
            status &= ~1;
            lines_per_frame = 262;
          }

          /* reinitialize VC max value */
          switch (bitmap.viewport.h)
          {
            case 192:
              vc_max = vc_table[0][vdp_pal];
              break;
            case 224:
              vc_max = vc_table[1][vdp_pal];
              break;
            case 240:
              vc_max = vc_table[3][vdp_pal];
              break;
          }
        }
        break;
      }

      case SDLK_F10:
      {
        gen_reset(0);
        break;
      }

      case SDLK_F11:
      {
        config.overscan =  (config.overscan + 1) & 3;
        if ((system_hw == SYSTEM_GG) && !config.gg_extra)
        {
          bitmap.viewport.x = (config.overscan & 2) ? 14 : -48;
        }
        else
        {
          bitmap.viewport.x = (config.overscan & 2) * 7;
        }
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