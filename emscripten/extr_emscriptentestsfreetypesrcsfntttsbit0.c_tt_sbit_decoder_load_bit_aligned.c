#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ width; scalar_t__ rows; scalar_t__ pitch; int* buffer; } ;
struct TYPE_7__ {TYPE_1__* metrics; TYPE_3__* bitmap; int /*<<< orphan*/  bitmap_allocated; } ;
struct TYPE_6__ {scalar_t__ width; scalar_t__ height; } ;
typedef  TYPE_2__* TT_SBitDecoder ;
typedef  int FT_UShort ;
typedef  scalar_t__ FT_Int ;
typedef  scalar_t__ FT_Error ;
typedef  int FT_Byte ;
typedef  TYPE_3__ FT_Bitmap ;

/* Variables and functions */
 scalar_t__ SFNT_Err_Invalid_File_Format ; 
 scalar_t__ SFNT_Err_Ok ; 
 scalar_t__ tt_sbit_decoder_alloc_bitmap (TYPE_2__*) ; 

__attribute__((used)) static FT_Error
  tt_sbit_decoder_load_bit_aligned( TT_SBitDecoder  decoder,
                                    FT_Byte*        p,
                                    FT_Byte*        limit,
                                    FT_Int          x_pos,
                                    FT_Int          y_pos )
  {
    FT_Error    error = SFNT_Err_Ok;
    FT_Byte*    line;
    FT_Int      bit_height, bit_width, pitch, width, height, h, nbits;
    FT_Bitmap*  bitmap;
    FT_UShort   rval;


    if ( !decoder->bitmap_allocated )
    {
      error = tt_sbit_decoder_alloc_bitmap( decoder );
      if ( error )
        goto Exit;
    }

    /* check that we can write the glyph into the bitmap */
    bitmap     = decoder->bitmap;
    bit_width  = bitmap->width;
    bit_height = bitmap->rows;
    pitch      = bitmap->pitch;
    line       = bitmap->buffer;

    width  = decoder->metrics->width;
    height = decoder->metrics->height;

    if ( x_pos < 0 || x_pos + width  > bit_width  ||
         y_pos < 0 || y_pos + height > bit_height )
    {
      error = SFNT_Err_Invalid_File_Format;
      goto Exit;
    }

    if ( p + ( ( width * height + 7 ) >> 3 ) > limit )
    {
      error = SFNT_Err_Invalid_File_Format;
      goto Exit;
    }

    /* now do the blit */

    /* adjust `line' to point to the first byte of the bitmap */
    line  += y_pos * pitch + ( x_pos >> 3 );
    x_pos &= 7;

    /* the higher byte of `rval' is used as a buffer */
    rval  = 0;
    nbits = 0;

    for ( h = height; h > 0; h--, line += pitch )
    {
      FT_Byte*  write = line;
      FT_Int    w     = width;


      /* handle initial byte (in target bitmap) specially if necessary */
      if ( x_pos )
      {
        w = ( width < 8 - x_pos ) ? width : 8 - x_pos;

        if ( h == height )
        {
          rval  = *p++;
          nbits = x_pos;
        }
        else if ( nbits < w )
        {
          if ( p < limit )
            rval |= *p++;
          nbits += 8 - w;
        }
        else
        {
          rval  >>= 8;
          nbits  -= w;
        }

        *write++ |= ( ( rval >> nbits ) & 0xFF ) &
                    ( ~( 0xFF << w ) << ( 8 - w - x_pos ) );
        rval    <<= 8;

        w = width - w;
      }

      /* handle medial bytes */
      for ( ; w >= 8; w -= 8 )
      {
        rval     |= *p++;
        *write++ |= ( rval >> nbits ) & 0xFF;

        rval <<= 8;
      }

      /* handle final byte if necessary */
      if ( w > 0 )
      {
        if ( nbits < w )
        {
          if ( p < limit )
            rval |= *p++;
          *write |= ( ( rval >> nbits ) & 0xFF ) & ( 0xFF00U >> w );
          nbits  += 8 - w;

          rval <<= 8;
        }
        else
        {
          *write |= ( ( rval >> nbits ) & 0xFF ) & ( 0xFF00U >> w );
          nbits  -= w;
        }
      }
    }

  Exit:
    return error;
  }