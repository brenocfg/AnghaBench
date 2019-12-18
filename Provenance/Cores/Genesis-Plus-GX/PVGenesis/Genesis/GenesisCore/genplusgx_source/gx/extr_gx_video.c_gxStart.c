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
struct TYPE_2__ {int /*<<< orphan*/  view; int /*<<< orphan*/  up; int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  Mtx ;

/* Variables and functions */
 int DEFAULT_FIFO_SIZE ; 
 int /*<<< orphan*/  GX_ALWAYS ; 
 int /*<<< orphan*/  GX_CLIP_DISABLE ; 
 int /*<<< orphan*/  GX_CULL_NONE ; 
 int /*<<< orphan*/  GX_FALSE ; 
 int /*<<< orphan*/  GX_Flush () ; 
 int /*<<< orphan*/  GX_GM_1_0 ; 
 int /*<<< orphan*/  GX_Init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GX_LoadPosMtxImm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_PF_RGB8_Z24 ; 
 int /*<<< orphan*/  GX_PNMTX0 ; 
 int /*<<< orphan*/  GX_SetAlphaUpdate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetClipMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetColorUpdate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetCullMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetDispCopyGamma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetPixelFmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetZMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_TRUE ; 
 int /*<<< orphan*/  GX_ZC_LINEAR ; 
 TYPE_1__ cam ; 
 int /*<<< orphan*/  gp_fifo ; 
 int /*<<< orphan*/  guLookAt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gxStart(void)
{
  /*** Clear out FIFO area ***/
  memset(&gp_fifo, 0, DEFAULT_FIFO_SIZE);

  /*** GX default ***/
  GX_Init(&gp_fifo, DEFAULT_FIFO_SIZE);
  GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
  GX_SetCullMode(GX_CULL_NONE);
  GX_SetClipMode(GX_CLIP_DISABLE);
  GX_SetDispCopyGamma(GX_GM_1_0);
  GX_SetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
  GX_SetColorUpdate(GX_TRUE);
  GX_SetAlphaUpdate(GX_FALSE);

  /* Modelview */
  Mtx view;
  memset (&view, 0, sizeof (Mtx));
  guLookAt(view, &cam.pos, &cam.up, &cam.view);
  GX_LoadPosMtxImm(view, GX_PNMTX0);
  GX_Flush();
}