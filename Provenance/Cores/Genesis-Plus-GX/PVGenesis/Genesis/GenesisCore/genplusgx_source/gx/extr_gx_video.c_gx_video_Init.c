#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_12__ {void* viTVMode; } ;
struct TYPE_11__ {void* viTVMode; } ;
struct TYPE_10__ {void* viTVMode; } ;
struct TYPE_9__ {int viTVMode; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_BLACK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FONT_Init () ; 
 int /*<<< orphan*/  GX_TRUE ; 
 int HASPECT ; 
 scalar_t__ MEM_K0_TO_K1 (int /*<<< orphan*/ *) ; 
 scalar_t__ SYS_AllocateFramebuffer (int /*<<< orphan*/ *) ; 
 int TEX_SIZE ; 
 int /*<<< orphan*/  TV50hz_576i ; 
 TYPE_8__ TV60hz_240i ; 
 TYPE_7__ TV60hz_240p ; 
 TYPE_6__ TV60hz_480i ; 
 int VASPECT ; 
 int /*<<< orphan*/  VIDEO_ClearFrameBuffer (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEO_Configure (TYPE_1__*) ; 
 int /*<<< orphan*/  VIDEO_Flush () ; 
 TYPE_1__* VIDEO_GetPreferredMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VIDEO_Init () ; 
 int /*<<< orphan*/  VIDEO_SetBlack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEO_SetNextFramebuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VIDEO_WaitVSync () ; 
 int /*<<< orphan*/  VI_INTERLACE ; 
 int /*<<< orphan*/  VI_NON_INTERLACE ; 
#define  VI_PAL 128 
 void* VI_TVMODE (int,int /*<<< orphan*/ ) ; 
 void* VI_TVMODE_EURGB60_DS ; 
 void* VI_TVMODE_EURGB60_INT ; 
 int /*<<< orphan*/  console_init (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  gxResetMode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxResetRendering (int) ; 
 int /*<<< orphan*/  gxStart () ; 
 void* memalign (int,int) ; 
 void* screenshot ; 
 void* texturemem ; 
 TYPE_1__* vmode ; 
 int /*<<< orphan*/ ** xfb ; 

void gx_video_Init(void)
{
  /*
   * Before doing anything else under libogc,
   * Call VIDEO_Init
   */
  VIDEO_Init();

  /* Get the current VIDEO mode then :
      - set menu video mode (480p/576p/480i/576i)
      - set emulator rendering 60hz TV modes (PAL/MPAL/NTSC/EURGB60)
   */
  vmode = VIDEO_GetPreferredMode(NULL);

  /* Adjust display settings */
  switch (vmode->viTVMode >> 2)
  {
    case VI_PAL:  /* 576 lines scaled (PAL 50Hz) */
      TV60hz_240p.viTVMode = VI_TVMODE_EURGB60_DS;
      TV60hz_240i.viTVMode = VI_TVMODE_EURGB60_INT;
      TV60hz_480i.viTVMode = VI_TVMODE_EURGB60_INT;
      break;
    
    default:  /* 480 lines (NTSC, MPAL or PAL 60Hz) */
      TV60hz_240p.viTVMode = VI_TVMODE(vmode->viTVMode >> 2, VI_NON_INTERLACE);
      TV60hz_240i.viTVMode = VI_TVMODE(vmode->viTVMode >> 2, VI_INTERLACE);
      TV60hz_480i.viTVMode = VI_TVMODE(vmode->viTVMode >> 2, VI_INTERLACE);
      break;
  }

  /* Configure VI */
  VIDEO_Configure (vmode);

  /* Configure the framebuffers (double-buffering) */
  xfb[0] = (u32 *) MEM_K0_TO_K1((u32 *) SYS_AllocateFramebuffer(&TV50hz_576i));
  xfb[1] = (u32 *) MEM_K0_TO_K1((u32 *) SYS_AllocateFramebuffer(&TV50hz_576i));

  /* Define a console */
  console_init(xfb[0], 20, 64, 640, 574, 574 * 2);

  /* Clear framebuffers to black */
  VIDEO_ClearFrameBuffer(vmode, xfb[0], COLOR_BLACK);
  VIDEO_ClearFrameBuffer(vmode, xfb[1], COLOR_BLACK);

  /* Set the framebuffer to be displayed at next VBlank */
  VIDEO_SetNextFramebuffer(xfb[0]);

  /* Enable Video Interface */
  VIDEO_SetBlack(FALSE);

  /* Update VIDEO settings for next VBlank */
  VIDEO_Flush();

  /* Wait for VBlank */
  VIDEO_WaitVSync();
  VIDEO_WaitVSync();

  /* Initialize GX */
  gxStart();
  gxResetRendering(1);
  gxResetMode(vmode, GX_TRUE);

  /* initialize FONT */
  FONT_Init();

  /* Initialize textures */
  texturemem = memalign(32, TEX_SIZE);
  screenshot = memalign(32, HASPECT*VASPECT*4);
}