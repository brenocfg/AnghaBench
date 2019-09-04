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
struct TYPE_3__ {scalar_t__ subtable_length; } ;
typedef  TYPE_1__* GXV_Validator ;
typedef  void* FT_ULong ;
typedef  void* FT_Fixed ;
typedef  scalar_t__ FT_Bytes ;

/* Variables and functions */
 void* FT_NEXT_ULONG (scalar_t__) ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 

__attribute__((used)) static void
  gxv_just_actSubrecord_type4_validate( FT_Bytes       table,
                                        FT_Bytes       limit,
                                        GXV_Validator  valid )
  {
    FT_Bytes  p = table;
    FT_ULong  variantsAxis;
    FT_Fixed  minimumLimit;
    FT_Fixed  noStretchValue;
    FT_Fixed  maximumLimit;


    GXV_LIMIT_CHECK( 4 + 4 + 4 + 4 );
    variantsAxis   = FT_NEXT_ULONG( p );
    minimumLimit   = FT_NEXT_ULONG( p );
    noStretchValue = FT_NEXT_ULONG( p );
    maximumLimit   = FT_NEXT_ULONG( p );

    valid->subtable_length = p - table;
  }