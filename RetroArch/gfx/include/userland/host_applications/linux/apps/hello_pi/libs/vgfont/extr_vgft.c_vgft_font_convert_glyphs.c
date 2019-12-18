#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  float VGfloat ;
typedef  scalar_t__ VGPath ;
struct TYPE_13__ {TYPE_6__* ft_face; int /*<<< orphan*/  vg_font; } ;
typedef  TYPE_3__ VGFT_FONT_T ;
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
struct TYPE_15__ {TYPE_2__* glyph; } ;
struct TYPE_14__ {scalar_t__ n_contours; int /*<<< orphan*/  n_points; int /*<<< orphan*/  contours; int /*<<< orphan*/  tags; int /*<<< orphan*/  points; } ;
struct TYPE_11__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_12__ {TYPE_1__ advance; TYPE_4__ outline; } ;
typedef  scalar_t__ FT_ULong ;
typedef  int /*<<< orphan*/  FT_UInt ;
typedef  TYPE_4__ FT_Outline ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_Face (TYPE_6__*) ; 
 scalar_t__ FT_Get_First_Char (TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ FT_Get_Next_Char (TYPE_6__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FT_LOAD_DEFAULT ; 
 scalar_t__ FT_Load_Glyph (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FT_Set_Char_Size (TYPE_6__*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  VCOS_EINVAL ; 
 int /*<<< orphan*/  VCOS_ENOMEM ; 
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  VG_FALSE ; 
 scalar_t__ VG_INVALID_HANDLE ; 
 int /*<<< orphan*/  VG_PATH_CAPABILITY_ALL ; 
 int /*<<< orphan*/  VG_PATH_DATATYPE_F ; 
 int /*<<< orphan*/  VG_PATH_FORMAT_STANDARD ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  convert_outline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coords ; 
 float float_from_26_6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  segments ; 
 int /*<<< orphan*/  segments_count ; 
 int /*<<< orphan*/  vgAppendPathData (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vgCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgDestroyFont (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgDestroyPath (scalar_t__) ; 
 int /*<<< orphan*/  vgSetGlyphToPath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,float*,float*) ; 

VCOS_STATUS_T vgft_font_convert_glyphs(VGFT_FONT_T *font, unsigned int char_height, unsigned int dpi_x, unsigned int dpi_y)
{
   FT_UInt glyph_index;
   FT_ULong ch;

   if (FT_Set_Char_Size(font->ft_face, 0, char_height, dpi_x, dpi_y))
   {
      FT_Done_Face(font->ft_face);
      vgDestroyFont(font->vg_font);
      return VCOS_EINVAL;
   }

   ch = FT_Get_First_Char(font->ft_face, &glyph_index);

   while (ch != 0)
   {
      if (FT_Load_Glyph(font->ft_face, glyph_index, FT_LOAD_DEFAULT)) {
         FT_Done_Face(font->ft_face);
         vgDestroyFont(font->vg_font);
         return VCOS_ENOMEM;
      }

      VGPath vg_path;
      FT_Outline *outline = &font->ft_face->glyph->outline;
      if (outline->n_contours != 0) {
         vg_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
         assert(vg_path != VG_INVALID_HANDLE);

         convert_outline(outline->points, outline->tags, outline->contours, outline->n_contours, outline->n_points);
         vgAppendPathData(vg_path, segments_count, segments, coords);
      } else {
         vg_path = VG_INVALID_HANDLE;
      }

      VGfloat origin[] = { 0.0f, 0.0f };
      VGfloat escapement[] = { float_from_26_6(font->ft_face->glyph->advance.x), float_from_26_6(font->ft_face->glyph->advance.y) };
      vgSetGlyphToPath(font->vg_font, glyph_index, vg_path, VG_FALSE, origin, escapement);

      if (vg_path != VG_INVALID_HANDLE) {
         vgDestroyPath(vg_path);
      }
      ch = FT_Get_Next_Char(font->ft_face, ch, &glyph_index);
   }

   return VCOS_SUCCESS;
}