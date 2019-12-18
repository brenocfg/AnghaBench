#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int width; unsigned int height; int /*<<< orphan*/  is_threaded; scalar_t__ fullscreen; scalar_t__ rgb32; } ;
typedef  TYPE_3__ video_info_t ;
struct TYPE_16__ {scalar_t__ video_font_enable; } ;
struct TYPE_15__ {int /*<<< orphan*/  video_context_driver; } ;
struct TYPE_18__ {TYPE_2__ bools; TYPE_1__ arrays; } ;
typedef  TYPE_4__ settings_t ;
typedef  int /*<<< orphan*/  input_driver_t ;
struct TYPE_19__ {unsigned int width; unsigned int height; scalar_t__ fullscreen; } ;
typedef  TYPE_5__ gfx_ctx_mode_t ;
struct TYPE_20__ {void** input_data; int /*<<< orphan*/  const** input; } ;
typedef  TYPE_6__ gfx_ctx_input_t ;
struct TYPE_21__ {int /*<<< orphan*/  ident; } ;
typedef  TYPE_7__ gfx_ctx_driver_t ;
typedef  void fpga_t ;

/* Variables and functions */
 int /*<<< orphan*/  FONT_DRIVER_RENDER_FPGA ; 
 int /*<<< orphan*/  GFX_CTX_FPGA_API ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_4__* config_get_ptr () ; 
 int /*<<< orphan*/  font_driver_init_osd (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpga_gfx_create (void*) ; 
 scalar_t__ fpga_rgb32 ; 
 int fpga_video_bits ; 
 unsigned int fpga_video_height ; 
 int fpga_video_pitch ; 
 int fpga_video_width ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  video_context_driver_destroy () ; 
 int /*<<< orphan*/  video_context_driver_get_video_size (TYPE_5__*) ; 
 TYPE_7__* video_context_driver_init_first (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_context_driver_input_driver (TYPE_6__*) ; 
 int /*<<< orphan*/  video_context_driver_set (TYPE_7__ const*) ; 
 int /*<<< orphan*/  video_context_driver_set_video_mode (TYPE_5__*) ; 
 int /*<<< orphan*/  video_driver_get_size (unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  video_driver_set_size (unsigned int*,unsigned int*) ; 

__attribute__((used)) static void *fpga_gfx_init(const video_info_t *video,
      const input_driver_t **input, void **input_data)
{
   unsigned full_x, full_y;
   gfx_ctx_input_t inp;
   gfx_ctx_mode_t mode;
   const gfx_ctx_driver_t *ctx_driver   = NULL;
   unsigned win_width = 0, win_height   = 0;
   unsigned temp_width = 0, temp_height = 0;
   settings_t *settings                 = config_get_ptr();
   fpga_t *fpga                         = (fpga_t*)calloc(1, sizeof(*fpga));

   *input                               = NULL;
   *input_data                          = NULL;

   fpga_video_width                      = video->width;
   fpga_video_height                     = video->height;
   fpga_rgb32                            = video->rgb32;

   fpga_video_bits                       = video->rgb32 ? 32 : 16;

   if (video->rgb32)
      fpga_video_pitch = video->width * 4;
   else
      fpga_video_pitch = video->width * 2;

   fpga_gfx_create(fpga);

   ctx_driver = video_context_driver_init_first(fpga,
         settings->arrays.video_context_driver,
         GFX_CTX_FPGA_API, 1, 0, false);
   if (!ctx_driver)
      goto error;

   video_context_driver_set((const gfx_ctx_driver_t*)ctx_driver);

   RARCH_LOG("[FPGA]: Found FPGA context: %s\n", ctx_driver->ident);

   video_context_driver_get_video_size(&mode);

   full_x      = mode.width;
   full_y      = mode.height;
   mode.width  = 0;
   mode.height = 0;

   RARCH_LOG("[FPGA]: Detecting screen resolution %ux%u.\n", full_x, full_y);

   win_width   = video->width;
   win_height  = video->height;

   if (video->fullscreen && (win_width == 0) && (win_height == 0))
   {
      win_width  = full_x;
      win_height = full_y;
   }

   mode.width      = win_width;
   mode.height     = win_height;
   mode.fullscreen = video->fullscreen;

   if (!video_context_driver_set_video_mode(&mode))
      goto error;

   mode.width     = 0;
   mode.height    = 0;

   video_context_driver_get_video_size(&mode);

   temp_width     = mode.width;
   temp_height    = mode.height;
   mode.width     = 0;
   mode.height    = 0;

   /* Get real known video size, which might have been altered by context. */

   if (temp_width != 0 && temp_height != 0)
      video_driver_set_size(&temp_width, &temp_height);

   video_driver_get_size(&temp_width, &temp_height);

   RARCH_LOG("[FPGA]: Using resolution %ux%u\n", temp_width, temp_height);

   inp.input      = input;
   inp.input_data = input_data;

   video_context_driver_input_driver(&inp);

   if (settings->bools.video_font_enable)
      font_driver_init_osd(NULL, false,
            video->is_threaded,
            FONT_DRIVER_RENDER_FPGA);

   RARCH_LOG("[FPGA]: Init complete.\n");

   return fpga;

error:
   video_context_driver_destroy();
   if (fpga)
      free(fpga);
   return NULL;
}