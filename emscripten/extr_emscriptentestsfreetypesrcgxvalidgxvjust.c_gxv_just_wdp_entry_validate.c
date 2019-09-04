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
typedef  int /*<<< orphan*/  FT_UShort ;
typedef  void* FT_ULong ;
typedef  void* FT_Fixed ;
typedef  scalar_t__ FT_Bytes ;

/* Variables and functions */
 void* FT_NEXT_ULONG (scalar_t__) ; 
 int /*<<< orphan*/  FT_NEXT_USHORT (scalar_t__) ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 

__attribute__((used)) static void
  gxv_just_wdp_entry_validate( FT_Bytes       table,
                               FT_Bytes       limit,
                               GXV_Validator  valid )
  {
    FT_Bytes   p = table;
    FT_ULong   justClass;
    FT_Fixed   beforeGrowLimit;
    FT_Fixed   beforeShrinkGrowLimit;
    FT_Fixed   afterGrowLimit;
    FT_Fixed   afterShrinkGrowLimit;
    FT_UShort  growFlags;
    FT_UShort  shrinkFlags;


    GXV_LIMIT_CHECK( 4 + 4 + 4 + 4 + 4 + 2 + 2 );
    justClass             = FT_NEXT_ULONG( p );
    beforeGrowLimit       = FT_NEXT_ULONG( p );
    beforeShrinkGrowLimit = FT_NEXT_ULONG( p );
    afterGrowLimit        = FT_NEXT_ULONG( p );
    afterShrinkGrowLimit  = FT_NEXT_ULONG( p );
    growFlags             = FT_NEXT_USHORT( p );
    shrinkFlags           = FT_NEXT_USHORT( p );

    /* TODO: decode flags for human readability */

    valid->subtable_length = p - table;
  }