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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ VGint ;
typedef  scalar_t__ VGfloat ;
typedef  int /*<<< orphan*/  VGPaint ;
typedef  int /*<<< orphan*/  VGFT_FONT_T ;
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
struct TYPE_4__ {scalar_t__ width; scalar_t__ height; } ;
typedef  int /*<<< orphan*/  GX_DISPLAY_T ;
typedef  int /*<<< orphan*/  GX_CLIENT_STATE_T ;
typedef  TYPE_1__* GRAPHICS_RESOURCE_HANDLE ;

/* Variables and functions */
 scalar_t__ GRAPHICS_RESOURCE_HEIGHT ; 
 scalar_t__ GRAPHICS_RESOURCE_WIDTH ; 
 scalar_t__ GRAPHICS_TRANSPARENT_COLOUR ; 
 int /*<<< orphan*/  GX_LOG (char*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VCOS_ENOMEM ; 
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  VG_CLEAR_COLOR ; 
 int /*<<< orphan*/  VG_FALSE ; 
 int /*<<< orphan*/  VG_FILL_PATH ; 
 int /*<<< orphan*/  VG_PAINT_COLOR ; 
 int /*<<< orphan*/  VG_PAINT_TYPE ; 
 int /*<<< orphan*/  VG_PAINT_TYPE_COLOR ; 
 int /*<<< orphan*/  VG_SCISSORING ; 
 int /*<<< orphan*/  VG_SCISSOR_RECTS ; 
 int /*<<< orphan*/  VG_TRUE ; 
 int /*<<< orphan*/ * find_font (char const*,scalar_t__) ; 
 int /*<<< orphan*/  gx_priv_colour_to_paint (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gx_priv_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gx_priv_save (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  inited ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_demand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgClear (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vgCreatePaint () ; 
 int /*<<< orphan*/  vgDestroyPaint (int /*<<< orphan*/ ) ; 
 int vgGetError () ; 
 int /*<<< orphan*/  vgSetPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgSetParameterfv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  vgSetParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgSetfv (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  vgSeti (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgSetiv (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ vgft_first_line_y_offset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgft_font_draw (int /*<<< orphan*/ *,scalar_t__,scalar_t__,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgft_get_text_extents (int /*<<< orphan*/ *,char const*,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 

VCOS_STATUS_T gx_priv_render_text( GX_DISPLAY_T *disp,
                                   GRAPHICS_RESOURCE_HANDLE res,
                                   int32_t x,
                                   int32_t y,
                                   uint32_t width,
                                   uint32_t height,
                                   uint32_t fg_colour,
                                   uint32_t bg_colour,
                                   const char *text,
                                   uint32_t text_length,
                                   uint32_t text_size )
{
   VGfloat vg_colour[4];
   VGFT_FONT_T *font;
   VGPaint fg;
   GX_CLIENT_STATE_T save;
   VCOS_STATUS_T status = VCOS_SUCCESS;
   int clip = 1;

   vcos_demand(inited); // has gx_font_init() been called?

   gx_priv_save(&save, res);

   if (width == GRAPHICS_RESOURCE_WIDTH &&
       height == GRAPHICS_RESOURCE_HEIGHT)
   {
      clip = 0;
   }

   width = (width == GRAPHICS_RESOURCE_WIDTH) ? res->width : width;
   height = (height == GRAPHICS_RESOURCE_HEIGHT) ? res->height : height;
   font = find_font(text, text_size);
   if (!font)
   {
      status = VCOS_ENOMEM;
      goto finish;
   }

   // setup the clipping rectangle
   if (clip)
   {
      VGint coords[] = {x,y,width,height};
      vgSeti(VG_SCISSORING, VG_TRUE);
      vgSetiv(VG_SCISSOR_RECTS, 4, coords);
   }

   // setup the background colour if needed
   if (bg_colour != GRAPHICS_TRANSPARENT_COLOUR)
   {
      int err;
      VGfloat rendered_w, rendered_h;
      VGfloat vg_bg_colour[4];

      // setup the background colour...
      gx_priv_colour_to_paint(bg_colour, vg_bg_colour);
      vgSetfv(VG_CLEAR_COLOR, 4, vg_bg_colour);

      // fill in a rectangle...
      vgft_get_text_extents(font, text, text_length, (VGfloat)x, (VGfloat)y, &rendered_w, &rendered_h);

      if ( ( 0 < (VGint)rendered_w ) && ( 0 < (VGint)rendered_h ) )
      {
         // Have to compensate for the messed up y position of multiline text.
         VGfloat offset = vgft_first_line_y_offset(font);
         int32_t bottom = y + offset - rendered_h;

         vgClear(x, bottom, (VGint)rendered_w, (VGint)rendered_h);
         err = vgGetError();
         if (err)
         {
            GX_LOG("Error %d clearing bg text %d %d %g %g",
                   err, x, y, rendered_w, rendered_h);
            vcos_assert(0);
         } // if
      } // if
   } // if
   // setup the foreground colour
   fg = vgCreatePaint();
   if (!fg)
   {
      status = VCOS_ENOMEM;
      goto finish;
   }

   // draw the foreground text
   vgSetParameteri(fg, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
   gx_priv_colour_to_paint(fg_colour, vg_colour);
   vgSetParameterfv(fg, VG_PAINT_COLOR, 4, vg_colour);
   vgSetPaint(fg, VG_FILL_PATH);

   vgft_font_draw(font, (VGfloat)x, (VGfloat)y, text, text_length, VG_FILL_PATH);

   vgDestroyPaint(fg);

   vcos_assert(vgGetError() == 0);
   vgSeti(VG_SCISSORING, VG_FALSE);

finish:
   gx_priv_restore(&save);

   return status;
}