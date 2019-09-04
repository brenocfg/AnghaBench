#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* glyph; int /*<<< orphan*/  stream; } ;
struct TYPE_12__ {int sbit_table_size; int /*<<< orphan*/ * sbit_table; TYPE_2__ root; scalar_t__ (* goto_table ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_11__ {int ebdt_size; int strike_index_array; int strike_index_count; int /*<<< orphan*/  bit_depth; int /*<<< orphan*/ * eblc_base; int /*<<< orphan*/ * eblc_limit; int /*<<< orphan*/  ebdt_start; scalar_t__ bitmap_allocated; scalar_t__ metrics_loaded; int /*<<< orphan*/ * metrics; int /*<<< orphan*/ * bitmap; int /*<<< orphan*/  stream; TYPE_4__* face; } ;
struct TYPE_9__ {int /*<<< orphan*/  bitmap; } ;
typedef  int /*<<< orphan*/  TT_SBit_MetricsRec ;
typedef  TYPE_3__* TT_SBitDecoder ;
typedef  TYPE_4__* TT_Face ;
typedef  int FT_ULong ;
typedef  int /*<<< orphan*/  FT_Stream ;
typedef  scalar_t__ FT_Error ;
typedef  int /*<<< orphan*/  FT_Byte ;

/* Variables and functions */
 void* FT_NEXT_ULONG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FT_STREAM_POS () ; 
 scalar_t__ SFNT_Err_Invalid_File_Format ; 
 int /*<<< orphan*/  TTAG_EBDT ; 
 int /*<<< orphan*/  TTAG_bdat ; 
 scalar_t__ stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static FT_Error
  tt_sbit_decoder_init( TT_SBitDecoder       decoder,
                        TT_Face              face,
                        FT_ULong             strike_index,
                        TT_SBit_MetricsRec*  metrics )
  {
    FT_Error   error;
    FT_Stream  stream = face->root.stream;
    FT_ULong   ebdt_size;


    error = face->goto_table( face, TTAG_EBDT, stream, &ebdt_size );
    if ( error )
      error = face->goto_table( face, TTAG_bdat, stream, &ebdt_size );
    if ( error )
      goto Exit;

    decoder->face    = face;
    decoder->stream  = stream;
    decoder->bitmap  = &face->root.glyph->bitmap;
    decoder->metrics = metrics;

    decoder->metrics_loaded   = 0;
    decoder->bitmap_allocated = 0;

    decoder->ebdt_start = FT_STREAM_POS();
    decoder->ebdt_size  = ebdt_size;

    decoder->eblc_base  = face->sbit_table;
    decoder->eblc_limit = face->sbit_table + face->sbit_table_size;

    /* now find the strike corresponding to the index */
    {
      FT_Byte*  p;


      if ( 8 + 48 * strike_index + 3 * 4 + 34 + 1 > face->sbit_table_size )
      {
        error = SFNT_Err_Invalid_File_Format;
        goto Exit;
      }

      p = decoder->eblc_base + 8 + 48 * strike_index;

      decoder->strike_index_array = FT_NEXT_ULONG( p );
      p                          += 4;
      decoder->strike_index_count = FT_NEXT_ULONG( p );
      p                          += 34;
      decoder->bit_depth          = *p;

      if ( decoder->strike_index_array > face->sbit_table_size             ||
           decoder->strike_index_array + 8 * decoder->strike_index_count >
             face->sbit_table_size                                         )
        error = SFNT_Err_Invalid_File_Format;
    }

  Exit:
    return error;
  }