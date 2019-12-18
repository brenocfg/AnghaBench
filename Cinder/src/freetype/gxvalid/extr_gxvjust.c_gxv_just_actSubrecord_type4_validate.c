#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int subtable_length; } ;
typedef  TYPE_1__* GXV_Validator ;
typedef  int FT_ULong ;
typedef  scalar_t__ FT_Fixed ;
typedef  scalar_t__ FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_DATA ; 
 scalar_t__ FT_NEXT_LONG (scalar_t__) ; 
 int FT_NEXT_ULONG (scalar_t__) ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 
 int /*<<< orphan*/  IS_PARANOID_VALIDATION ; 

__attribute__((used)) static void
  gxv_just_actSubrecord_type4_validate( FT_Bytes       table,
                                        FT_Bytes       limit,
                                        GXV_Validator  gxvalid )
  {
    FT_Bytes  p = table;
    FT_ULong  variantsAxis;
    FT_Fixed  minimumLimit;
    FT_Fixed  noStretchValue;
    FT_Fixed  maximumLimit;


    GXV_LIMIT_CHECK( 4 + 4 + 4 + 4 );
    variantsAxis   = FT_NEXT_ULONG( p );
    minimumLimit   = FT_NEXT_LONG( p );
    noStretchValue = FT_NEXT_LONG( p );
    maximumLimit   = FT_NEXT_LONG( p );

    gxvalid->subtable_length = (FT_ULong)( p - table );

    if ( variantsAxis != 0x64756374L ) /* 'duct' */
      GXV_TRACE(( "variantsAxis 0x%08x is non default value",
                   variantsAxis ));

    if ( minimumLimit > noStretchValue )
      GXV_TRACE(( "type4:minimumLimit 0x%08x > noStretchValue 0x%08x\n",
                  minimumLimit, noStretchValue ));
    else if ( noStretchValue > maximumLimit )
      GXV_TRACE(( "type4:noStretchValue 0x%08x > maximumLimit 0x%08x\n",
                  noStretchValue, maximumLimit ));
    else if ( !IS_PARANOID_VALIDATION )
      return;

    FT_INVALID_DATA;
  }