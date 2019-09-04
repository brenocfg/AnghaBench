#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pixel_mode; } ;
struct TYPE_6__ {TYPE_1__ bitmap; } ;
typedef  int /*<<< orphan*/  FT_Vector ;
typedef  int /*<<< orphan*/  FT_Renderer ;
typedef  int /*<<< orphan*/  FT_Render_Mode ;
typedef  TYPE_2__* FT_GlyphSlot ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_PIXEL_MODE_LCD_V ; 
 int /*<<< orphan*/  FT_RENDER_MODE_LCD_V ; 
 int /*<<< orphan*/  ft_smooth_render_generic (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  ft_smooth_render_lcd_v( FT_Renderer       render,
                          FT_GlyphSlot      slot,
                          FT_Render_Mode    mode,
                          const FT_Vector*  origin )
  {
    FT_Error  error;

    error = ft_smooth_render_generic( render, slot, mode, origin,
                                      FT_RENDER_MODE_LCD_V );
    if ( !error )
      slot->bitmap.pixel_mode = FT_PIXEL_MODE_LCD_V;

    return error;
  }