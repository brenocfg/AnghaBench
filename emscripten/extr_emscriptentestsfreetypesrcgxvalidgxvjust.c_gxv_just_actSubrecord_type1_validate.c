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
typedef  scalar_t__ FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_NEXT_USHORT (scalar_t__) ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 

__attribute__((used)) static void
  gxv_just_actSubrecord_type1_validate( FT_Bytes       table,
                                        FT_Bytes       limit,
                                        GXV_Validator  valid )
  {
    FT_Bytes   p = table;
    FT_UShort  addGlyph;


    GXV_LIMIT_CHECK( 2 );
    addGlyph = FT_NEXT_USHORT( p );

    valid->subtable_length = p - table;
  }