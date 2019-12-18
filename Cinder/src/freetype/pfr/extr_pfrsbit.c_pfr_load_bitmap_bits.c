#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rows; scalar_t__ width; } ;
typedef  int /*<<< orphan*/  PFR_BitWriterRec ;
typedef  int FT_UInt ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int /*<<< orphan*/  FT_Byte ;
typedef  int /*<<< orphan*/  FT_Bool ;
typedef  TYPE_1__ FT_Bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 
 int /*<<< orphan*/  pfr_bitwriter_decode_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfr_bitwriter_decode_rle1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfr_bitwriter_decode_rle2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfr_bitwriter_init (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  pfr_load_bitmap_bits( FT_Byte*    p,
                        FT_Byte*    limit,
                        FT_UInt     format,
                        FT_Bool     decreasing,
                        FT_Bitmap*  target )
  {
    FT_Error          error = FT_Err_Ok;
    PFR_BitWriterRec  writer;


    if ( target->rows > 0 && target->width > 0 )
    {
      pfr_bitwriter_init( &writer, target, decreasing );

      switch ( format )
      {
      case 0: /* packed bits */
        pfr_bitwriter_decode_bytes( &writer, p, limit );
        break;

      case 1: /* RLE1 */
        pfr_bitwriter_decode_rle1( &writer, p, limit );
        break;

      case 2: /* RLE2 */
        pfr_bitwriter_decode_rle2( &writer, p, limit );
        break;

      default:
        ;
      }
    }

    return error;
  }