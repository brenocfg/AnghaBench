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
typedef  scalar_t__ FT_UInt ;
typedef  scalar_t__ FT_Int ;
typedef  scalar_t__ FT_Error ;
typedef  int FT_Byte ;
typedef  TYPE_3__ FT_Bitmap ;

/* Variables and functions */
 scalar_t__ SFNT_Err_Invalid_File_Format ; 
 scalar_t__ SFNT_Err_Ok ; 
 scalar_t__ tt_sbit_decoder_alloc_bitmap (TYPE_2__*) ; 

__attribute__((used)) static FT_Error
  tt_sbit_decoder_load_byte_aligned( TT_SBitDecoder  decoder,
                                     FT_Byte*        p,
                                     FT_Byte*        limit,
                                     FT_Int          x_pos,
                                     FT_Int          y_pos )
  {
    FT_Error    error = SFNT_Err_Ok;
    FT_Byte*    line;
    FT_Int      bit_height, bit_width, pitch, width, height, h;
    FT_Bitmap*  bitmap;


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

    if ( x_pos < 0 || x_pos + width > bit_width   ||
         y_pos < 0 || y_pos + height > bit_height )
    {
      error = SFNT_Err_Invalid_File_Format;
      goto Exit;
    }

    if ( p + ( ( width + 7 ) >> 3 ) * height > limit )
    {
      error = SFNT_Err_Invalid_File_Format;
      goto Exit;
    }

    /* now do the blit */
    line  += y_pos * pitch + ( x_pos >> 3 );
    x_pos &= 7;

    if ( x_pos == 0 )  /* the easy one */
    {
      for ( h = height; h > 0; h--, line += pitch )
      {
        FT_Byte*  write = line;
        FT_Int    w;


        for ( w = width; w >= 8; w -= 8 )
        {
          write[0] = (FT_Byte)( write[0] | *p++ );
          write   += 1;
        }

        if ( w > 0 )
          write[0] = (FT_Byte)( write[0] | ( *p++ & ( 0xFF00U >> w ) ) );
      }
    }
    else  /* x_pos > 0 */
    {
      for ( h = height; h > 0; h--, line += pitch )
      {
        FT_Byte*  write = line;
        FT_Int    w;
        FT_UInt   wval = 0;


        for ( w = width; w >= 8; w -= 8 )
        {
          wval      = (FT_UInt)( wval | *p++ );
          write[0]  = (FT_Byte)( write[0] | ( wval >> x_pos ) );
          write    += 1;
          wval    <<= 8;
        }

        if ( w > 0 )
          wval = (FT_UInt)( wval | ( *p++ & ( 0xFF00U >> w ) ) );

        /* all bits read and there are `x_pos + w' bits to be written */

        write[0] = (FT_Byte)( write[0] | ( wval >> x_pos ) );

        if ( x_pos + w > 8 )
        {
          write++;
          wval   <<= 8;
          write[0] = (FT_Byte)( write[0] | ( wval >> x_pos ) );
        }
      }
    }

  Exit:
    return error;
  }