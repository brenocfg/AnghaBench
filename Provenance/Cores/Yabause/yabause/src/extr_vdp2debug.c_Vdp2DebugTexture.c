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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  pixel_t ;

/* Variables and functions */
 int /*<<< orphan*/  TITAN_BLEND_TOP ; 
 int /*<<< orphan*/  TitanGetResolution (int*,int*) ; 
 int /*<<< orphan*/  TitanInit () ; 
 int /*<<< orphan*/  TitanRender (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TitanSetBlendingMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDSoftVdp2DrawScreen (int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 

pixel_t *Vdp2DebugTexture(u32 screen, int * w, int * h)
{
   pixel_t * bitmap;

   TitanInit();
   TitanSetBlendingMode(TITAN_BLEND_TOP);
   VIDSoftVdp2DrawScreen(screen);

   if ((bitmap = (pixel_t *)calloc(sizeof(pixel_t), 704 * 512)) == NULL)
      return NULL;

   TitanGetResolution(w, h);

   TitanRender(bitmap);

   return bitmap;
}