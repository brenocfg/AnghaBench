#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ ebdt_size; scalar_t__ ebdt_start; int /*<<< orphan*/  stream; } ;
typedef  scalar_t__ (* TT_SBitDecoder_LoadFunc ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  TYPE_1__* TT_SBitDecoder ;
typedef  scalar_t__ FT_ULong ;
typedef  int FT_UInt ;
typedef  int /*<<< orphan*/  FT_Stream ;
typedef  int /*<<< orphan*/  FT_Int ;
typedef  scalar_t__ FT_Error ;
typedef  int /*<<< orphan*/  FT_Byte ;

/* Variables and functions */
 scalar_t__ FT_FRAME_EXTRACT (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FT_FRAME_RELEASE (int /*<<< orphan*/ *) ; 
 scalar_t__ FT_STREAM_SEEK (scalar_t__) ; 
 scalar_t__ SFNT_Err_Invalid_Argument ; 
 scalar_t__ SFNT_Err_Ok ; 
 scalar_t__ tt_sbit_decoder_load_bit_aligned (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tt_sbit_decoder_load_byte_aligned (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tt_sbit_decoder_load_compound (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tt_sbit_decoder_load_metrics (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static FT_Error
  tt_sbit_decoder_load_bitmap( TT_SBitDecoder  decoder,
                               FT_UInt         glyph_format,
                               FT_ULong        glyph_start,
                               FT_ULong        glyph_size,
                               FT_Int          x_pos,
                               FT_Int          y_pos )
  {
    FT_Error   error;
    FT_Stream  stream = decoder->stream;
    FT_Byte*   p;
    FT_Byte*   p_limit;
    FT_Byte*   data;


    /* seek into the EBDT table now */
    if ( glyph_start + glyph_size > decoder->ebdt_size )
    {
      error = SFNT_Err_Invalid_Argument;
      goto Exit;
    }

    if ( FT_STREAM_SEEK( decoder->ebdt_start + glyph_start ) ||
         FT_FRAME_EXTRACT( glyph_size, data )                )
      goto Exit;

    p       = data;
    p_limit = p + glyph_size;

    /* read the data, depending on the glyph format */
    switch ( glyph_format )
    {
    case 1:
    case 2:
    case 8:
      error = tt_sbit_decoder_load_metrics( decoder, &p, p_limit, 0 );
      break;

    case 6:
    case 7:
    case 9:
      error = tt_sbit_decoder_load_metrics( decoder, &p, p_limit, 1 );
      break;

    default:
      error = SFNT_Err_Ok;
    }

    if ( error )
      goto Fail;

    {
      TT_SBitDecoder_LoadFunc  loader;


      switch ( glyph_format )
      {
      case 1:
      case 6:
        loader = tt_sbit_decoder_load_byte_aligned;
        break;

      case 2:
      case 5:
      case 7:
        loader = tt_sbit_decoder_load_bit_aligned;
        break;

      case 8:
        if ( p + 1 > p_limit )
          goto Fail;

        p += 1;  /* skip padding */
        /* fall-through */

      case 9:
        loader = tt_sbit_decoder_load_compound;
        break;

      default:
        goto Fail;
      }

      error = loader( decoder, p, p_limit, x_pos, y_pos );
    }

  Fail:
    FT_FRAME_RELEASE( data );

  Exit:
    return error;
  }