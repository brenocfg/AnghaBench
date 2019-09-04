#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int ul; } ;
struct TYPE_8__ {int /*<<< orphan*/  optdata; } ;
struct TYPE_11__ {TYPE_2__* root; TYPE_1__ xstatetable; } ;
struct TYPE_10__ {scalar_t__ substitutionTable_num_lookupTables; } ;
struct TYPE_9__ {scalar_t__ level; } ;
typedef  TYPE_3__* GXV_morx_subtable_type1_StateOptRecData ;
typedef  TYPE_4__* GXV_Validator ;
typedef  TYPE_5__* GXV_StateTable_GlyphOffsetCPtr ;
typedef  int FT_UShort ;
typedef  scalar_t__ FT_Short ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_DATA ; 
 int /*<<< orphan*/  FT_UNUSED (int) ; 
 scalar_t__ FT_VALIDATE_PARANOID ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 

__attribute__((used)) static void
  gxv_morx_subtable_type1_entry_validate(
    FT_UShort                       state,
    FT_UShort                       flags,
    GXV_StateTable_GlyphOffsetCPtr  glyphOffset_p,
    FT_Bytes                        table,
    FT_Bytes                        limit,
    GXV_Validator                   valid )
  {
    FT_UShort  setMark;
    FT_UShort  dontAdvance;
    FT_UShort  reserved;
    FT_Short   markIndex;
    FT_Short   currentIndex;

    GXV_morx_subtable_type1_StateOptRecData  optdata =
      (GXV_morx_subtable_type1_StateOptRecData)valid->xstatetable.optdata;

    FT_UNUSED( state );
    FT_UNUSED( table );
    FT_UNUSED( limit );


    setMark      = (FT_UShort)( ( flags >> 15 ) & 1 );
    dontAdvance  = (FT_UShort)( ( flags >> 14 ) & 1 );

    reserved = (FT_UShort)( flags & 0x3FFF );

    markIndex    = (FT_Short)( glyphOffset_p->ul >> 16 );
    currentIndex = (FT_Short)( glyphOffset_p->ul       );

    GXV_TRACE(( " setMark=%01d dontAdvance=%01d\n",
                setMark, dontAdvance ));

    if ( 0 < reserved )
    {
      GXV_TRACE(( " non-zero bits found in reserved range\n" ));
      if ( valid->root->level >= FT_VALIDATE_PARANOID )
        FT_INVALID_DATA;
    }

    GXV_TRACE(( "markIndex = %d, currentIndex = %d\n",
                markIndex, currentIndex ));

    if ( optdata->substitutionTable_num_lookupTables < markIndex + 1 )
      optdata->substitutionTable_num_lookupTables =
        (FT_Short)( markIndex + 1 );

    if ( optdata->substitutionTable_num_lookupTables < currentIndex + 1 )
      optdata->substitutionTable_num_lookupTables =
        (FT_Short)( currentIndex + 1 );
  }