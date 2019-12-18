#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct retro_hw_ps2_insets {float left; float right; float top; float bottom; } ;
struct TYPE_8__ {float Width; float Height; } ;
struct TYPE_7__ {float Width; float Height; } ;
typedef  TYPE_1__ GSTEXTURE ;
typedef  TYPE_2__ GSGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  GS_TEXT ; 
 float MIN (float,float) ; 
 int /*<<< orphan*/  gsKit_prim_sprite_texture (TYPE_2__*,TYPE_1__*,float,float,float,float,float,float,float,float,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prim_texture(GSGLOBAL *gsGlobal, GSTEXTURE *texture, int zPosition, bool force_aspect, struct retro_hw_ps2_insets padding)
{
      float x1, y1, x2, y2;
      float visible_width =  texture->Width - padding.left - padding.right;
      float visible_height =  texture->Height - padding.top - padding.bottom;
   if (force_aspect) {
      float width_proportion = (float)gsGlobal->Width / (float)visible_width;
      float height_proportion = (float)gsGlobal->Height / (float)visible_height;
      float delta = MIN(width_proportion, height_proportion);
      float newWidth = visible_width * delta;
      float newHeight = visible_height * delta;

      x1 = (gsGlobal->Width - newWidth) / 2.0f;
      y1 = (gsGlobal->Height - newHeight) / 2.0f;
      x2 = newWidth + x1;
      y2 = newHeight + y1;

   } else {
      x1 = 0.0f;
      y1 = 0.0f;
      x2 = gsGlobal->Width;
      y2 = gsGlobal->Height;
   }

   gsKit_prim_sprite_texture( gsGlobal, texture,
                              x1, //X1
                              y1,  // Y1
                              padding.left,  // U1
                              padding.top,  // V1
                              x2, // X2
                              y2, // Y2
                              texture->Width - padding.right, // U2
                              texture->Height - padding.bottom, // V2
                              zPosition,
                              GS_TEXT);
}