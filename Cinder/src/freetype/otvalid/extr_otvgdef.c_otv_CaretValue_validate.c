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
typedef  int /*<<< orphan*/  OTV_Validator ;
typedef  int FT_UInt ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_FORMAT ; 
 int FT_NEXT_USHORT (int) ; 
 int /*<<< orphan*/  OTV_ENTER ; 
 int /*<<< orphan*/  OTV_EXIT ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_TRACE (char*) ; 
 int /*<<< orphan*/  otv_Device_validate (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  otv_CaretValue_validate( FT_Bytes       table,
                           OTV_Validator  otvalid )
  {
    FT_Bytes  p = table;
    FT_UInt   CaretValueFormat;


    OTV_ENTER;

    OTV_LIMIT_CHECK( 4 );

    CaretValueFormat = FT_NEXT_USHORT( p );

    OTV_TRACE(( " (format = %d)\n", CaretValueFormat ));

    switch ( CaretValueFormat )
    {
    case 1:     /* CaretValueFormat1 */
      /* skip Coordinate, no test */
      break;

    case 2:     /* CaretValueFormat2 */
      /* skip CaretValuePoint, no test */
      break;

    case 3:     /* CaretValueFormat3 */
      p += 2;   /* skip Coordinate */

      OTV_LIMIT_CHECK( 2 );

      /* DeviceTable */
      otv_Device_validate( table + FT_NEXT_USHORT( p ), otvalid );
      break;

    default:
      FT_INVALID_FORMAT;
    }

    OTV_EXIT;
  }