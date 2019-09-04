#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  subtable_length; } ;
typedef  TYPE_1__* GXV_Validator ;
typedef  int FT_UShort ;
typedef  int /*<<< orphan*/  FT_ULong ;
typedef  int /*<<< orphan*/  FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_DATA ; 
 int /*<<< orphan*/  FT_NEXT_ULONG (int /*<<< orphan*/ ) ; 
 int FT_NEXT_USHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_EXIT ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  gxv_just_actSubrecord_type0_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gxv_just_actSubrecord_type1_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gxv_just_actSubrecord_type2_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gxv_just_actSubrecord_type4_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gxv_just_actSubrecord_type5_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
  gxv_just_actSubrecord_validate( FT_Bytes       table,
                                  FT_Bytes       limit,
                                  GXV_Validator  valid )
  {
    FT_Bytes   p = table;
    FT_UShort  actionClass;
    FT_UShort  actionType;
    FT_ULong   actionLength;


    GXV_NAME_ENTER( "just actSubrecord" );

    GXV_LIMIT_CHECK( 2 + 2 + 4 );
    actionClass  = FT_NEXT_USHORT( p );
    actionType   = FT_NEXT_USHORT( p );
    actionLength = FT_NEXT_ULONG( p );

    if ( actionType == 0 )
      gxv_just_actSubrecord_type0_validate( p, limit, valid );
    else if ( actionType == 1 )
      gxv_just_actSubrecord_type1_validate( p, limit, valid );
    else if ( actionType == 2 )
      gxv_just_actSubrecord_type2_validate( p, limit, valid );
    else if ( actionType == 3 )
      ;                         /* Stretch glyph action: no actionData */
    else if ( actionType == 4 )
      gxv_just_actSubrecord_type4_validate( p, limit, valid );
    else if ( actionType == 5 )
      gxv_just_actSubrecord_type5_validate( p, limit, valid );
    else
      FT_INVALID_DATA;

    valid->subtable_length = actionLength;

    GXV_EXIT;
  }