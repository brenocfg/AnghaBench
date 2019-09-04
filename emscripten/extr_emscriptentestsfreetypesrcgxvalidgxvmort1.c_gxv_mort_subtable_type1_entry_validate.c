#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int ul; } ;
struct TYPE_8__ {TYPE_1__* root; } ;
struct TYPE_7__ {scalar_t__ level; } ;
typedef  TYPE_2__* GXV_Validator ;
typedef  TYPE_3__* GXV_StateTable_GlyphOffsetCPtr ;
typedef  int FT_UShort ;
typedef  int FT_Short ;
typedef  int /*<<< orphan*/  FT_Bytes ;
typedef  int /*<<< orphan*/  FT_Byte ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_DATA ; 
 int /*<<< orphan*/  FT_UNUSED (int /*<<< orphan*/ ) ; 
 scalar_t__ FT_VALIDATE_PARANOID ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 
 int /*<<< orphan*/  gxv_mort_subtable_type1_offset_to_subst_validate (int,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
  gxv_mort_subtable_type1_entry_validate(
    FT_Byte                         state,
    FT_UShort                       flags,
    GXV_StateTable_GlyphOffsetCPtr  glyphOffset_p,
    FT_Bytes                        table,
    FT_Bytes                        limit,
    GXV_Validator                   valid )
  {
    FT_UShort  setMark;
    FT_UShort  dontAdvance;
    FT_UShort  reserved;
    FT_Short   markOffset;
    FT_Short   currentOffset;

    FT_UNUSED( table );
    FT_UNUSED( limit );


    setMark       = (FT_UShort)(   flags >> 15            );
    dontAdvance   = (FT_UShort)( ( flags >> 14 ) & 1      );
    reserved      = (FT_Short)(    flags         & 0x3FFF );

    markOffset    = (FT_Short)( glyphOffset_p->ul >> 16 );
    currentOffset = (FT_Short)( glyphOffset_p->ul       );

    if ( 0 < reserved )
    {
      GXV_TRACE(( " non-zero bits found in reserved range\n" ));
      if ( valid->root->level >= FT_VALIDATE_PARANOID )
        FT_INVALID_DATA;
    }

    gxv_mort_subtable_type1_offset_to_subst_validate( markOffset,
                                                      "markOffset",
                                                      state,
                                                      valid );

    gxv_mort_subtable_type1_offset_to_subst_validate( currentOffset,
                                                      "currentOffset",
                                                      state,
                                                      valid );
  }