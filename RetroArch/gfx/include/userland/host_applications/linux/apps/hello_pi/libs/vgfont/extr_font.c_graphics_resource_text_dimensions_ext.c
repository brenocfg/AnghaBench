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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  VGfloat ;
typedef  int /*<<< orphan*/  VGFT_FONT_T ;
typedef  int /*<<< orphan*/  GX_CLIENT_STATE_T ;
typedef  int /*<<< orphan*/  GRAPHICS_RESOURCE_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/ * find_font (char const*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gx_priv_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gx_priv_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgft_get_text_extents (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const,double,double,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int32_t graphics_resource_text_dimensions_ext(GRAPHICS_RESOURCE_HANDLE res,
                                              const char *text,
                                              const uint32_t text_length,
                                              uint32_t *width,
                                              uint32_t *height,
                                              const uint32_t text_size )
{
   GX_CLIENT_STATE_T save;
   VGfloat w, h;
   int ret = -1;

   gx_priv_save(&save, res);

   VGFT_FONT_T *font = find_font(text, text_size);
   if (!font)
      goto finish;

   vgft_get_text_extents(font, text, text_length, 0.0, 0.0, &w, &h);
   *width = w;
   *height = h;
   ret = 0;

finish:
   gx_priv_restore(&save);
   return ret;
}