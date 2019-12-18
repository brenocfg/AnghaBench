#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_11__ {scalar_t__ id; } ;
struct TYPE_12__ {TYPE_1__ current; } ;
struct TYPE_13__ {int pal_enable; scalar_t__ pal60_enable; TYPE_2__ resolutions; } ;
struct TYPE_14__ {TYPE_3__ screen; } ;
struct TYPE_15__ {TYPE_4__ console; } ;
typedef  TYPE_5__ global_t ;
typedef  void gfx_ctx_ps3_data_t ;
struct TYPE_17__ {int enable; int width; int height; int /*<<< orphan*/  rescRatioMode; int /*<<< orphan*/  rescPalTemporalMode; int /*<<< orphan*/  multisamplingMode; int /*<<< orphan*/  depthFormat; int /*<<< orphan*/  colorFormat; } ;
struct TYPE_16__ {int enable; int maxSPUs; int /*<<< orphan*/  initializeSPUs; } ;
typedef  TYPE_6__ PSGLinitOptions ;
typedef  TYPE_7__ PSGLdeviceParameters ;

/* Variables and functions */
 int /*<<< orphan*/  CELL_VIDEO_OUT_ASPECT_AUTO ; 
 int /*<<< orphan*/  CELL_VIDEO_OUT_PRIMARY ; 
 int /*<<< orphan*/  CELL_VIDEO_OUT_RESOLUTION_576 ; 
 int /*<<< orphan*/  GL_ARGB_SCE ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_MULTISAMPLING_NONE_SCE ; 
 int /*<<< orphan*/  GL_NONE ; 
 int PSGL_DEVICE_PARAMETERS_COLOR_FORMAT ; 
 int PSGL_DEVICE_PARAMETERS_DEPTH_FORMAT ; 
 int PSGL_DEVICE_PARAMETERS_MULTISAMPLING_MODE ; 
 int PSGL_DEVICE_PARAMETERS_RESC_PAL_TEMPORAL_MODE ; 
 int PSGL_DEVICE_PARAMETERS_RESC_RATIO_MODE ; 
 int PSGL_DEVICE_PARAMETERS_WIDTH_HEIGHT ; 
 int PSGL_INIT_INITIALIZE_SPUS ; 
 int PSGL_INIT_MAX_SPUS ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  RESC_PAL_TEMPORAL_MODE_60_INTERPOLATE ; 
 int /*<<< orphan*/  RESC_RATIO_MODE_FULLSCREEN ; 
 scalar_t__ calloc (int,int) ; 
 int cellVideoOutGetResolutionAvailability (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfx_ctx_ps3_get_available_resolutions () ; 
 int /*<<< orphan*/  gfx_ctx_ps3_get_resolution (scalar_t__,int*,int*) ; 
 TYPE_5__* global_get_ptr () ; 
 int /*<<< orphan*/  psglCreateContext () ; 
 int /*<<< orphan*/  psglCreateDeviceExtended (TYPE_7__*) ; 
 int /*<<< orphan*/  psglInit (TYPE_6__*) ; 
 int /*<<< orphan*/  psglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psglResetCurrentContext () ; 
 int /*<<< orphan*/  sys_spu_initialize (int,int) ; 

__attribute__((used)) static void *gfx_ctx_ps3_init(video_frame_info_t *video_info, void *video_driver)
{
#ifdef HAVE_PSGL
   PSGLdeviceParameters params;
   PSGLinitOptions options;
#endif
   global_t *global = global_get_ptr();
   gfx_ctx_ps3_data_t *ps3 = (gfx_ctx_ps3_data_t*)
      calloc(1, sizeof(gfx_ctx_ps3_data_t));

   (void)video_driver;
   (void)global;

   if (!ps3)
      return NULL;

#if defined(HAVE_PSGL)
   options.enable         = PSGL_INIT_MAX_SPUS | PSGL_INIT_INITIALIZE_SPUS;
   options.maxSPUs        = 1;
   options.initializeSPUs = GL_FALSE;

   /* Initialize 6 SPUs but reserve 1 SPU as a raw SPU for PSGL. */
   sys_spu_initialize(6, 1);
   psglInit(&options);

   params.enable            =
      PSGL_DEVICE_PARAMETERS_COLOR_FORMAT |
      PSGL_DEVICE_PARAMETERS_DEPTH_FORMAT |
      PSGL_DEVICE_PARAMETERS_MULTISAMPLING_MODE;
   params.colorFormat       = GL_ARGB_SCE;
   params.depthFormat       = GL_NONE;
   params.multisamplingMode = GL_MULTISAMPLING_NONE_SCE;

   if (global->console.screen.resolutions.current.id)
   {
      params.enable |= PSGL_DEVICE_PARAMETERS_WIDTH_HEIGHT;

      gfx_ctx_ps3_get_resolution(
            global->console.screen.resolutions.current.id,
            &params.width, &params.height);

      global->console.screen.pal_enable = false;

      if (params.width == 720 && params.height == 576)
      {
         RARCH_LOG("[PSGL Context]: 720x576 resolution detected, setting MODE_VIDEO_PAL_ENABLE.\n");
         global->console.screen.pal_enable = true;
      }
   }

   if (global->console.screen.pal60_enable)
   {
      RARCH_LOG("[PSGL Context]: Setting temporal PAL60 mode.\n");
      params.enable |= PSGL_DEVICE_PARAMETERS_RESC_PAL_TEMPORAL_MODE;
      params.enable |= PSGL_DEVICE_PARAMETERS_RESC_RATIO_MODE;
      params.rescPalTemporalMode = RESC_PAL_TEMPORAL_MODE_60_INTERPOLATE;
      params.rescRatioMode = RESC_RATIO_MODE_FULLSCREEN;
   }

   ps3->gl_device = psglCreateDeviceExtended(&params);
   ps3->gl_context = psglCreateContext();

   psglMakeCurrent(ps3->gl_context, ps3->gl_device);
   psglResetCurrentContext();
#endif

   global->console.screen.pal_enable =
      cellVideoOutGetResolutionAvailability(
            CELL_VIDEO_OUT_PRIMARY, CELL_VIDEO_OUT_RESOLUTION_576,
            CELL_VIDEO_OUT_ASPECT_AUTO, 0);

   gfx_ctx_ps3_get_available_resolutions();

   return ps3;
}