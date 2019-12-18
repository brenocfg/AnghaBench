#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
typedef  void orbis_ctx_data_t ;
struct TYPE_3__ {int size; int flags; int processOrder; int systemSharedMemorySize; int videoSharedMemorySize; int maxMappedFlexibleMemory; int drawCommandBufferSize; int lcueResourceBufferSize; int unk_0x5C; scalar_t__ dbgPosCmd_0x4C; scalar_t__ dbgPosCmd_0x48; int /*<<< orphan*/  dbgPosCmd_0x44; int /*<<< orphan*/  dbgPosCmd_0x40; } ;
typedef  int EGLint ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_ORBISGL_HEIGHT ; 
 int /*<<< orphan*/  ATTR_ORBISGL_WIDTH ; 
#define  EGL_ALPHA_SIZE 140 
#define  EGL_BLUE_SIZE 139 
 int /*<<< orphan*/  EGL_DEFAULT_DISPLAY ; 
#define  EGL_DEPTH_SIZE 138 
#define  EGL_GREEN_SIZE 137 
#define  EGL_NONE 136 
#define  EGL_OPENGL_ES2_BIT 135 
#define  EGL_RED_SIZE 134 
#define  EGL_RENDERABLE_TYPE 133 
#define  EGL_SAMPLES 132 
#define  EGL_SAMPLE_BUFFERS 131 
#define  EGL_STENCIL_SIZE 130 
#define  EGL_SURFACE_TYPE 129 
#define  EGL_WINDOW_BIT 128 
 int SCE_PGL_FLAGS_USE_COMPOSITE_EXT ; 
 int SCE_PGL_FLAGS_USE_FLEXIBLE_MEMORY ; 
 scalar_t__ calloc (int,int) ; 
 int eglGetError () ; 
 int /*<<< orphan*/  egl_init_context (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ,int*,int*,int*,int const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  egl_report_error () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* nx_ctx_ptr ; 
 int /*<<< orphan*/  orbis_ctx_destroy (void*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int scePigletSetConfigurationVSH (TYPE_1__*) ; 

__attribute__((used)) static void *orbis_ctx_init(video_frame_info_t *video_info, void *video_driver)
{
#ifdef HAVE_EGL
    int ret;
    EGLint n;
    EGLint major, minor;
    static const EGLint attribs[] = {
        EGL_RED_SIZE, 8,
         EGL_GREEN_SIZE, 8,
         EGL_BLUE_SIZE, 8,
         EGL_ALPHA_SIZE, 8,
         EGL_DEPTH_SIZE, 16,
         EGL_STENCIL_SIZE, 0,
         EGL_SAMPLE_BUFFERS, 0,
         EGL_SAMPLES, 0,
         EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
         EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
         EGL_NONE};
#endif

    orbis_ctx_data_t *ctx_orbis = (orbis_ctx_data_t *)calloc(1, sizeof(*ctx_orbis));

    if (!ctx_orbis)
        return NULL;

    nx_ctx_ptr = ctx_orbis;

#ifdef HAVE_EGL

   memset(&ctx_orbis->pgl_config, 0, sizeof(ctx_orbis->pgl_config));
   {
      ctx_orbis->pgl_config.size=sizeof(ctx_orbis->pgl_config);
      ctx_orbis->pgl_config.flags=SCE_PGL_FLAGS_USE_COMPOSITE_EXT | SCE_PGL_FLAGS_USE_FLEXIBLE_MEMORY | 0x60;
      ctx_orbis->pgl_config.processOrder=1;
      ctx_orbis->pgl_config.systemSharedMemorySize=0x200000;
      ctx_orbis->pgl_config.videoSharedMemorySize=0x2400000;
      ctx_orbis->pgl_config.maxMappedFlexibleMemory=0xAA00000;
      ctx_orbis->pgl_config.drawCommandBufferSize=0xC0000;
      ctx_orbis->pgl_config.lcueResourceBufferSize=0x10000;
      ctx_orbis->pgl_config.dbgPosCmd_0x40=ATTR_ORBISGL_WIDTH;
      ctx_orbis->pgl_config.dbgPosCmd_0x44=ATTR_ORBISGL_HEIGHT;
      ctx_orbis->pgl_config.dbgPosCmd_0x48=0;
      ctx_orbis->pgl_config.dbgPosCmd_0x4C=0;
      ctx_orbis->pgl_config.unk_0x5C=2;
   }
    ret = scePigletSetConfigurationVSH(&ctx_orbis->pgl_config);
    if (!ret)
    {
		  printf("[ORBISGL] scePigletSetConfigurationVSH failed 0x%08X.\n",ret);
        goto error;
    }

    if (!egl_init_context(&ctx_orbis->egl, EGL_NONE, EGL_DEFAULT_DISPLAY,
                          &major, &minor, &n, attribs, NULL))
    {
        egl_report_error();
        printf("[ORBIS]: EGL error: %d.\n", eglGetError());
        goto error;
    }
#endif

    return ctx_orbis;

error:
    orbis_ctx_destroy(video_driver);
    return NULL;
}