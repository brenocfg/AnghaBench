#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int xMin; int yMin; scalar_t__ xMax; scalar_t__ yMax; } ;
struct TYPE_20__ {int* buffer; int num_grays; int width; int rows; int pitch; int /*<<< orphan*/  pixel_mode; } ;
struct TYPE_19__ {scalar_t__ format; scalar_t__ bitmap_top; scalar_t__ bitmap_left; TYPE_2__* internal; TYPE_7__ bitmap; int /*<<< orphan*/  outline; } ;
struct TYPE_18__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * source; TYPE_7__* target; } ;
struct TYPE_14__ {int /*<<< orphan*/  memory; } ;
struct TYPE_17__ {scalar_t__ glyph_format; int /*<<< orphan*/  raster; scalar_t__ (* raster_render ) (int /*<<< orphan*/ ,TYPE_5__*) ;TYPE_1__ root; } ;
struct TYPE_16__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_15__ {int flags; } ;
typedef  TYPE_3__ FT_Vector ;
typedef  int FT_ULong ;
typedef  int FT_UInt ;
typedef  TYPE_4__* FT_Renderer ;
typedef  scalar_t__ FT_Render_Mode ;
typedef  TYPE_5__ FT_Raster_Params ;
typedef  scalar_t__ FT_Pos ;
typedef  int /*<<< orphan*/  FT_Outline ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  scalar_t__ FT_Int ;
typedef  TYPE_6__* FT_GlyphSlot ;
typedef  scalar_t__ FT_Error ;
typedef  int FT_Byte ;
typedef  TYPE_7__ FT_Bitmap ;
typedef  TYPE_8__ FT_BBox ;

/* Variables and functions */
 scalar_t__ FT_ALLOC (int*,int) ; 
 int /*<<< orphan*/  FT_ERROR (char*) ; 
 int /*<<< orphan*/  FT_FREE (int*) ; 
 scalar_t__ FT_GLYPH_FORMAT_BITMAP ; 
 int FT_GLYPH_OWN_BITMAP ; 
 scalar_t__ FT_INT_MAX ; 
 int /*<<< orphan*/  FT_Outline_Get_CBox (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  FT_Outline_Translate (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int FT_PAD_CEIL (int,int) ; 
 int /*<<< orphan*/  FT_PIXEL_MODE_GRAY ; 
 void* FT_PIX_CEIL (scalar_t__) ; 
 void* FT_PIX_FLOOR (int) ; 
 int /*<<< orphan*/  FT_RASTER_FLAG_AA ; 
 scalar_t__ FT_RENDER_MODE_LCD ; 
 scalar_t__ FT_RENDER_MODE_LCD_V ; 
 scalar_t__ Smooth_Err_Cannot_Render_Glyph ; 
 scalar_t__ Smooth_Err_Invalid_Argument ; 
 scalar_t__ Smooth_Err_Invalid_Pixel_Size ; 
 scalar_t__ Smooth_Err_Raster_Overflow ; 
 int /*<<< orphan*/  ft_memcpy (int*,int*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static FT_Error
  ft_smooth_render_generic( FT_Renderer       render,
                            FT_GlyphSlot      slot,
                            FT_Render_Mode    mode,
                            const FT_Vector*  origin,
                            FT_Render_Mode    required_mode )
  {
    FT_Error     error;
    FT_Outline*  outline = NULL;
    FT_BBox      cbox;
    FT_UInt      width, height, height_org, width_org, pitch;
    FT_Bitmap*   bitmap;
    FT_Memory    memory;
    FT_Int       hmul = mode == FT_RENDER_MODE_LCD;
    FT_Int       vmul = mode == FT_RENDER_MODE_LCD_V;
    FT_Pos       x_shift, y_shift, x_left, y_top;

    FT_Raster_Params  params;


    /* check glyph image format */
    if ( slot->format != render->glyph_format )
    {
      error = Smooth_Err_Invalid_Argument;
      goto Exit;
    }

    /* check mode */
    if ( mode != required_mode )
      return Smooth_Err_Cannot_Render_Glyph;

    outline = &slot->outline;

    /* translate the outline to the new origin if needed */
    if ( origin )
      FT_Outline_Translate( outline, origin->x, origin->y );

    /* compute the control box, and grid fit it */
    FT_Outline_Get_CBox( outline, &cbox );

    cbox.xMin = FT_PIX_FLOOR( cbox.xMin );
    cbox.yMin = FT_PIX_FLOOR( cbox.yMin );
    cbox.xMax = FT_PIX_CEIL( cbox.xMax );
    cbox.yMax = FT_PIX_CEIL( cbox.yMax );

    if ( cbox.xMin < 0 && cbox.xMax > FT_INT_MAX + cbox.xMin )
    {
      FT_ERROR(( "ft_smooth_render_generic: glyph too large:"
                 " xMin = %d, xMax = %d\n",
                 cbox.xMin >> 6, cbox.xMax >> 6 ));
      return Smooth_Err_Raster_Overflow;
    }
    else
      width  = (FT_UInt)( ( cbox.xMax - cbox.xMin ) >> 6 );

    if ( cbox.yMin < 0 && cbox.yMax > FT_INT_MAX + cbox.yMin )
    {
      FT_ERROR(( "ft_smooth_render_generic: glyph too large:"
                 " yMin = %d, yMax = %d\n",
                 cbox.yMin >> 6, cbox.yMax >> 6 ));
      return Smooth_Err_Raster_Overflow;
    }
    else
      height = (FT_UInt)( ( cbox.yMax - cbox.yMin ) >> 6 );

    bitmap = &slot->bitmap;
    memory = render->root.memory;

    width_org  = width;
    height_org = height;

    /* release old bitmap buffer */
    if ( slot->internal->flags & FT_GLYPH_OWN_BITMAP )
    {
      FT_FREE( bitmap->buffer );
      slot->internal->flags &= ~FT_GLYPH_OWN_BITMAP;
    }

    /* allocate new one */
    pitch = width;
    if ( hmul )
    {
      width = width * 3;
      pitch = FT_PAD_CEIL( width, 4 );
    }

    if ( vmul )
      height *= 3;

    x_shift = (FT_Int) cbox.xMin;
    y_shift = (FT_Int) cbox.yMin;
    x_left  = (FT_Int)( cbox.xMin >> 6 );
    y_top   = (FT_Int)( cbox.yMax >> 6 );

#ifdef FT_CONFIG_OPTION_SUBPIXEL_RENDERING

    if ( slot->library->lcd_filter_func )
    {
      FT_Int  extra = slot->library->lcd_extra;


      if ( hmul )
      {
        x_shift -= 64 * ( extra >> 1 );
        width   += 3 * extra;
        pitch    = FT_PAD_CEIL( width, 4 );
        x_left  -= extra >> 1;
      }

      if ( vmul )
      {
        y_shift -= 64 * ( extra >> 1 );
        height  += 3 * extra;
        y_top   += extra >> 1;
      }
    }

#endif

#if FT_UINT_MAX > 0xFFFFU

    /* Required check is ( pitch * height < FT_ULONG_MAX ),     */
    /* but we care realistic cases only. Always pitch <= width. */
    if ( width > 0x7FFFU || height > 0x7FFFU )
    {
      FT_ERROR(( "ft_smooth_render_generic: glyph too large: %u x %u\n",
                 width, height ));
      return Smooth_Err_Raster_Overflow;
    }

#endif

    bitmap->pixel_mode = FT_PIXEL_MODE_GRAY;
    bitmap->num_grays  = 256;
    bitmap->width      = width;
    bitmap->rows       = height;
    bitmap->pitch      = pitch;

    /* translate outline to render it into the bitmap */
    FT_Outline_Translate( outline, -x_shift, -y_shift );

    if ( FT_ALLOC( bitmap->buffer, (FT_ULong)pitch * height ) )
      goto Exit;

    slot->internal->flags |= FT_GLYPH_OWN_BITMAP;

    /* set up parameters */
    params.target = bitmap;
    params.source = outline;
    params.flags  = FT_RASTER_FLAG_AA;

#ifdef FT_CONFIG_OPTION_SUBPIXEL_RENDERING

    /* implode outline if needed */
    {
      FT_Vector*  points     = outline->points;
      FT_Vector*  points_end = points + outline->n_points;
      FT_Vector*  vec;


      if ( hmul )
        for ( vec = points; vec < points_end; vec++ )
          vec->x *= 3;

      if ( vmul )
        for ( vec = points; vec < points_end; vec++ )
          vec->y *= 3;
    }

    /* render outline into the bitmap */
    error = render->raster_render( render->raster, &params );

    /* deflate outline if needed */
    {
      FT_Vector*  points     = outline->points;
      FT_Vector*  points_end = points + outline->n_points;
      FT_Vector*  vec;


      if ( hmul )
        for ( vec = points; vec < points_end; vec++ )
          vec->x /= 3;

      if ( vmul )
        for ( vec = points; vec < points_end; vec++ )
          vec->y /= 3;
    }

    if ( slot->library->lcd_filter_func )
      slot->library->lcd_filter_func( bitmap, mode, slot->library );

#else /* !FT_CONFIG_OPTION_SUBPIXEL_RENDERING */

    /* render outline into bitmap */
    error = render->raster_render( render->raster, &params );

    /* expand it horizontally */
    if ( hmul )
    {
      FT_Byte*  line = bitmap->buffer;
      FT_UInt   hh;


      for ( hh = height_org; hh > 0; hh--, line += pitch )
      {
        FT_UInt   xx;
        FT_Byte*  end = line + width;


        for ( xx = width_org; xx > 0; xx-- )
        {
          FT_UInt  pixel = line[xx-1];


          end[-3] = (FT_Byte)pixel;
          end[-2] = (FT_Byte)pixel;
          end[-1] = (FT_Byte)pixel;
          end    -= 3;
        }
      }
    }

    /* expand it vertically */
    if ( vmul )
    {
      FT_Byte*  read  = bitmap->buffer + ( height - height_org ) * pitch;
      FT_Byte*  write = bitmap->buffer;
      FT_UInt   hh;


      for ( hh = height_org; hh > 0; hh-- )
      {
        ft_memcpy( write, read, pitch );
        write += pitch;

        ft_memcpy( write, read, pitch );
        write += pitch;

        ft_memcpy( write, read, pitch );
        write += pitch;
        read  += pitch;
      }
    }

#endif /* !FT_CONFIG_OPTION_SUBPIXEL_RENDERING */

    FT_Outline_Translate( outline, x_shift, y_shift );

    /*
     * XXX: on 16bit system, we return an error for huge bitmap
     * to prevent an overflow.
     */
    if ( x_left > FT_INT_MAX || y_top > FT_INT_MAX )
      return Smooth_Err_Invalid_Pixel_Size;

    if ( error )
      goto Exit;

    slot->format      = FT_GLYPH_FORMAT_BITMAP;
    slot->bitmap_left = (FT_Int)x_left;
    slot->bitmap_top  = (FT_Int)y_top;

  Exit:
    if ( outline && origin )
      FT_Outline_Translate( outline, -origin->x, -origin->y );

    return error;
  }