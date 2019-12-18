#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Filter; int /*<<< orphan*/  ClutPSM; int /*<<< orphan*/  PSM; int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; } ;
struct TYPE_5__ {TYPE_3__* Texture; } ;
typedef  int /*<<< orphan*/  GSGLOBAL ;
typedef  TYPE_1__ GSFONTM ;

/* Variables and functions */
 int /*<<< orphan*/  FONTM_TEXTURE_HEIGHT ; 
 int /*<<< orphan*/  FONTM_TEXTURE_WIDTH ; 
 int /*<<< orphan*/  GS_FILTER_LINEAR ; 
 int /*<<< orphan*/  GS_PSM_CT32 ; 
 int /*<<< orphan*/  GS_PSM_T4 ; 
 scalar_t__ gsKit_fontm_unpack (TYPE_1__*) ; 
 int /*<<< orphan*/  gsKit_setup_tbw (TYPE_3__*) ; 

__attribute__((used)) static void ps2_prepare_font(GSGLOBAL *gsGlobal, GSFONTM *gsFontM)
{  
   if(gsKit_fontm_unpack(gsFontM) == 0) {
      gsFontM->Texture->Width = FONTM_TEXTURE_WIDTH;
      gsFontM->Texture->Height = FONTM_TEXTURE_HEIGHT;
      gsFontM->Texture->PSM = GS_PSM_T4;
      gsFontM->Texture->ClutPSM = GS_PSM_CT32;
      gsFontM->Texture->Filter = GS_FILTER_LINEAR;
      gsKit_setup_tbw(gsFontM->Texture);
   }
}