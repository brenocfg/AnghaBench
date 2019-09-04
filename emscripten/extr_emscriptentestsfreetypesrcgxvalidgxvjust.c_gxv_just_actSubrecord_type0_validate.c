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
typedef  scalar_t__ FT_UShort ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Fixed ;
typedef  scalar_t__ FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_NEXT_ULONG (scalar_t__) ; 
 scalar_t__ FT_NEXT_USHORT (scalar_t__) ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 

__attribute__((used)) static void
  gxv_just_actSubrecord_type0_validate( FT_Bytes       table,
                                        FT_Bytes       limit,
                                        GXV_Validator  valid )
  {
    FT_Bytes   p = table;

    FT_Fixed   lowerLimit;
    FT_Fixed   upperLimit;

    FT_UShort  order;
    FT_UShort  decomposedCount;

    FT_UInt    i;


    GXV_LIMIT_CHECK( 4 + 4 + 2 + 2 );
    lowerLimit      = FT_NEXT_ULONG( p );
    upperLimit      = FT_NEXT_ULONG( p );
    order           = FT_NEXT_USHORT( p );
    decomposedCount = FT_NEXT_USHORT( p );

    for ( i = 0; i < decomposedCount; i++ )
    {
      FT_UShort glyphs;


      GXV_LIMIT_CHECK( 2 );
      glyphs = FT_NEXT_USHORT( p );
    }

    valid->subtable_length = p - table;
  }