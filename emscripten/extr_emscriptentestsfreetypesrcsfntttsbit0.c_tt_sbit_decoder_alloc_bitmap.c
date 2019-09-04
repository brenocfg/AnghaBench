#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int width; int rows; int pitch; int /*<<< orphan*/  pixel_mode; } ;
struct TYPE_10__ {int bit_depth; int bitmap_allocated; TYPE_3__* face; TYPE_1__* metrics; int /*<<< orphan*/  metrics_loaded; TYPE_5__* bitmap; } ;
struct TYPE_8__ {int /*<<< orphan*/  glyph; } ;
struct TYPE_9__ {TYPE_2__ root; } ;
struct TYPE_7__ {scalar_t__ height; scalar_t__ width; } ;
typedef  TYPE_4__* TT_SBitDecoder ;
typedef  scalar_t__ FT_UInt ;
typedef  int FT_Long ;
typedef  scalar_t__ FT_Error ;
typedef  TYPE_5__ FT_Bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  FT_PIXEL_MODE_GRAY ; 
 int /*<<< orphan*/  FT_PIXEL_MODE_GRAY2 ; 
 int /*<<< orphan*/  FT_PIXEL_MODE_GRAY4 ; 
 int /*<<< orphan*/  FT_PIXEL_MODE_MONO ; 
 scalar_t__ SFNT_Err_Invalid_Argument ; 
 scalar_t__ SFNT_Err_Invalid_File_Format ; 
 scalar_t__ SFNT_Err_Ok ; 
 scalar_t__ ft_glyphslot_alloc_bitmap (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static FT_Error
  tt_sbit_decoder_alloc_bitmap( TT_SBitDecoder  decoder )
  {
    FT_Error    error = SFNT_Err_Ok;
    FT_UInt     width, height;
    FT_Bitmap*  map = decoder->bitmap;
    FT_Long     size;


    if ( !decoder->metrics_loaded )
    {
      error = SFNT_Err_Invalid_Argument;
      goto Exit;
    }

    width  = decoder->metrics->width;
    height = decoder->metrics->height;

    map->width = (int)width;
    map->rows  = (int)height;

    switch ( decoder->bit_depth )
    {
    case 1:
      map->pixel_mode = FT_PIXEL_MODE_MONO;
      map->pitch      = ( map->width + 7 ) >> 3;
      break;

    case 2:
      map->pixel_mode = FT_PIXEL_MODE_GRAY2;
      map->pitch      = ( map->width + 3 ) >> 2;
      break;

    case 4:
      map->pixel_mode = FT_PIXEL_MODE_GRAY4;
      map->pitch      = ( map->width + 1 ) >> 1;
      break;

    case 8:
      map->pixel_mode = FT_PIXEL_MODE_GRAY;
      map->pitch      = map->width;
      break;

    default:
      error = SFNT_Err_Invalid_File_Format;
      goto Exit;
    }

    size = map->rows * map->pitch;

    /* check that there is no empty image */
    if ( size == 0 )
      goto Exit;     /* exit successfully! */

    error = ft_glyphslot_alloc_bitmap( decoder->face->root.glyph, size );
    if ( error )
      goto Exit;

    decoder->bitmap_allocated = 1;

  Exit:
    return error;
  }