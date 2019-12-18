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
 int /*<<< orphan*/  OTV_EXIT ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_OFFSET (int) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_TABLE (int) ; 
 int /*<<< orphan*/  OTV_SIZE_CHECK (int) ; 
 int /*<<< orphan*/  OTV_TRACE (char*) ; 
 int XDeviceTable ; 
 int YDeviceTable ; 
 int /*<<< orphan*/  otv_Device_validate (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  otv_Anchor_validate( FT_Bytes       table,
                       OTV_Validator  otvalid )
  {
    FT_Bytes  p = table;
    FT_UInt   AnchorFormat;


    OTV_NAME_ENTER( "Anchor");

    OTV_LIMIT_CHECK( 6 );
    AnchorFormat = FT_NEXT_USHORT( p );

    OTV_TRACE(( " (format %d)\n", AnchorFormat ));

    p += 4;     /* skip XCoordinate and YCoordinate */

    switch ( AnchorFormat )
    {
    case 1:
      break;

    case 2:
      OTV_LIMIT_CHECK( 2 );  /* AnchorPoint */
      break;

    case 3:
      {
        FT_UInt  table_size;

        OTV_OPTIONAL_TABLE( XDeviceTable );
        OTV_OPTIONAL_TABLE( YDeviceTable );


        OTV_LIMIT_CHECK( 4 );
        OTV_OPTIONAL_OFFSET( XDeviceTable );
        OTV_OPTIONAL_OFFSET( YDeviceTable );

        table_size = 6 + 4;

        OTV_SIZE_CHECK( XDeviceTable );
        if ( XDeviceTable )
          otv_Device_validate( table + XDeviceTable, otvalid );

        OTV_SIZE_CHECK( YDeviceTable );
        if ( YDeviceTable )
          otv_Device_validate( table + YDeviceTable, otvalid );
      }
      break;

    default:
      FT_INVALID_FORMAT;
    }

    OTV_EXIT;
  }