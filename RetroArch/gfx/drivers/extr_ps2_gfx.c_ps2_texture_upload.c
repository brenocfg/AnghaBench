#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ PSM; int Width; int Height; int TBW; scalar_t__ ClutPSM; int /*<<< orphan*/  Vram; int /*<<< orphan*/  Mem; int /*<<< orphan*/  VramClut; int /*<<< orphan*/  Clut; } ;
typedef  TYPE_1__ GSTEXTURE ;
typedef  int /*<<< orphan*/  GSGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  GS_CLUT_NONE ; 
 int /*<<< orphan*/  GS_CLUT_PALLETE ; 
 int /*<<< orphan*/  GS_CLUT_TEXTURE ; 
 scalar_t__ GS_PSM_T4 ; 
 scalar_t__ GS_PSM_T8 ; 
 int /*<<< orphan*/  gsKit_setup_tbw (TYPE_1__*) ; 
 int /*<<< orphan*/  gsKit_texture_send (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ps2_texture_upload(GSGLOBAL *gsGlobal, GSTEXTURE *Texture, bool sendPalette)
{
   gsKit_setup_tbw(Texture);

   if (Texture->PSM == GS_PSM_T8) {
      gsKit_texture_send(Texture->Mem, Texture->Width, Texture->Height, Texture->Vram, Texture->PSM, Texture->TBW, GS_CLUT_TEXTURE);
      if (sendPalette) {
         gsKit_texture_send(Texture->Clut, 16, 16, Texture->VramClut, Texture->ClutPSM, 1, GS_CLUT_PALLETE);
      }

   } else if (Texture->PSM == GS_PSM_T4) {
      gsKit_texture_send(Texture->Mem, Texture->Width, Texture->Height, Texture->Vram, Texture->PSM, Texture->TBW, GS_CLUT_TEXTURE);
      if (sendPalette) {
         gsKit_texture_send(Texture->Clut, 8,  2, Texture->VramClut, Texture->ClutPSM, 1, GS_CLUT_PALLETE);
      }
   } else {
      gsKit_texture_send(Texture->Mem, Texture->Width, Texture->Height, Texture->Vram, Texture->PSM, Texture->TBW, GS_CLUT_NONE);
   }
}