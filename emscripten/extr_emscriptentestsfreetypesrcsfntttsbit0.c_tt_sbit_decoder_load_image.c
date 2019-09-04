#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int strike_index_array; scalar_t__ strike_index_count; int /*<<< orphan*/ * eblc_base; int /*<<< orphan*/ * eblc_limit; } ;
typedef  TYPE_1__* TT_SBitDecoder ;
typedef  scalar_t__ FT_ULong ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Int ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int /*<<< orphan*/  FT_Byte ;

/* Variables and functions */
 scalar_t__ FT_NEXT_ULONG (int /*<<< orphan*/ *) ; 
 scalar_t__ FT_NEXT_USHORT (int /*<<< orphan*/ *) ; 
 scalar_t__ FT_PEEK_USHORT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SFNT_Err_Invalid_Argument ; 
 int /*<<< orphan*/  SFNT_Err_Invalid_Table ; 
 int /*<<< orphan*/  tt_sbit_decoder_load_bitmap (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tt_sbit_decoder_load_metrics (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static FT_Error
  tt_sbit_decoder_load_image( TT_SBitDecoder  decoder,
                              FT_UInt         glyph_index,
                              FT_Int          x_pos,
                              FT_Int          y_pos )
  {
    /*
     *  First, we find the correct strike range that applies to this
     *  glyph index.
     */

    FT_Byte*  p          = decoder->eblc_base + decoder->strike_index_array;
    FT_Byte*  p_limit    = decoder->eblc_limit;
    FT_ULong  num_ranges = decoder->strike_index_count;
    FT_UInt   start, end, index_format, image_format;
    FT_ULong  image_start = 0, image_end = 0, image_offset;


    for ( ; num_ranges > 0; num_ranges-- )
    {
      start = FT_NEXT_USHORT( p );
      end   = FT_NEXT_USHORT( p );

      if ( glyph_index >= start && glyph_index <= end )
        goto FoundRange;

      p += 4;  /* ignore index offset */
    }
    goto NoBitmap;

  FoundRange:
    image_offset = FT_NEXT_ULONG( p );

    /* overflow check */
    if ( decoder->eblc_base + decoder->strike_index_array + image_offset <
           decoder->eblc_base )
      goto Failure;

    p = decoder->eblc_base + decoder->strike_index_array + image_offset;
    if ( p + 8 > p_limit )
      goto NoBitmap;

    /* now find the glyph's location and extend within the ebdt table */
    index_format = FT_NEXT_USHORT( p );
    image_format = FT_NEXT_USHORT( p );
    image_offset = FT_NEXT_ULONG ( p );

    switch ( index_format )
    {
    case 1: /* 4-byte offsets relative to `image_offset' */
      {
        p += 4 * ( glyph_index - start );
        if ( p + 8 > p_limit )
          goto NoBitmap;

        image_start = FT_NEXT_ULONG( p );
        image_end   = FT_NEXT_ULONG( p );

        if ( image_start == image_end )  /* missing glyph */
          goto NoBitmap;
      }
      break;

    case 2: /* big metrics, constant image size */
      {
        FT_ULong  image_size;


        if ( p + 12 > p_limit )
          goto NoBitmap;

        image_size = FT_NEXT_ULONG( p );

        if ( tt_sbit_decoder_load_metrics( decoder, &p, p_limit, 1 ) )
          goto NoBitmap;

        image_start = image_size * ( glyph_index - start );
        image_end   = image_start + image_size;
      }
      break;

    case 3: /* 2-byte offsets relative to 'image_offset' */
      {
        p += 2 * ( glyph_index - start );
        if ( p + 4 > p_limit )
          goto NoBitmap;

        image_start = FT_NEXT_USHORT( p );
        image_end   = FT_NEXT_USHORT( p );

        if ( image_start == image_end )  /* missing glyph */
          goto NoBitmap;
      }
      break;

    case 4: /* sparse glyph array with (glyph,offset) pairs */
      {
        FT_ULong  mm, num_glyphs;


        if ( p + 4 > p_limit )
          goto NoBitmap;

        num_glyphs = FT_NEXT_ULONG( p );

        /* overflow check */
        if ( p + ( num_glyphs + 1 ) * 4 < p )
          goto Failure;

        if ( p + ( num_glyphs + 1 ) * 4 > p_limit )
          goto NoBitmap;

        for ( mm = 0; mm < num_glyphs; mm++ )
        {
          FT_UInt  gindex = FT_NEXT_USHORT( p );


          if ( gindex == glyph_index )
          {
            image_start = FT_NEXT_USHORT( p );
            p          += 2;
            image_end   = FT_PEEK_USHORT( p );
            break;
          }
          p += 2;
        }

        if ( mm >= num_glyphs )
          goto NoBitmap;
      }
      break;

    case 5: /* constant metrics with sparse glyph codes */
      {
        FT_ULong  image_size, mm, num_glyphs;


        if ( p + 16 > p_limit )
          goto NoBitmap;

        image_size = FT_NEXT_ULONG( p );

        if ( tt_sbit_decoder_load_metrics( decoder, &p, p_limit, 1 ) )
          goto NoBitmap;

        num_glyphs = FT_NEXT_ULONG( p );

        /* overflow check */
        if ( p + 2 * num_glyphs < p )
          goto Failure;

        if ( p + 2 * num_glyphs > p_limit )
          goto NoBitmap;

        for ( mm = 0; mm < num_glyphs; mm++ )
        {
          FT_UInt  gindex = FT_NEXT_USHORT( p );


          if ( gindex == glyph_index )
            break;
        }

        if ( mm >= num_glyphs )
          goto NoBitmap;

        image_start = image_size * mm;
        image_end   = image_start + image_size;
      }
      break;

    default:
      goto NoBitmap;
    }

    if ( image_start > image_end )
      goto NoBitmap;

    image_end  -= image_start;
    image_start = image_offset + image_start;

    return tt_sbit_decoder_load_bitmap( decoder,
                                        image_format,
                                        image_start,
                                        image_end,
                                        x_pos,
                                        y_pos );

  Failure:
    return SFNT_Err_Invalid_Table;

  NoBitmap:
    return SFNT_Err_Invalid_Argument;
  }