#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  u; } ;
typedef  int /*<<< orphan*/  GXV_Validator ;
typedef  TYPE_1__* GXV_StateTable_GlyphOffsetCPtr ;
typedef  size_t FT_UShort ;
typedef  TYPE_1__* FT_Bytes ;
typedef  TYPE_1__* FT_Byte ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_DATA ; 
 int /*<<< orphan*/  FT_UNUSED (TYPE_1__*) ; 
 TYPE_1__** GXV_Mort_IndicScript_Msg ; 
 int /*<<< orphan*/  GXV_SET_ERR_IF_PARANOID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 

__attribute__((used)) static void
  gxv_mort_subtable_type0_entry_validate(
    FT_Byte                         state,
    FT_UShort                       flags,
    GXV_StateTable_GlyphOffsetCPtr  glyphOffset_p,
    FT_Bytes                        table,
    FT_Bytes                        limit,
    GXV_Validator                   gxvalid )
  {
    FT_UShort  markFirst;
    FT_UShort  dontAdvance;
    FT_UShort  markLast;
    FT_UShort  reserved;
    FT_UShort  verb = 0;

    FT_UNUSED( state );
    FT_UNUSED( table );
    FT_UNUSED( limit );

    FT_UNUSED( GXV_Mort_IndicScript_Msg[verb] ); /* for the non-debugging */
    FT_UNUSED( glyphOffset_p );                  /* case                  */


    markFirst   = (FT_UShort)( ( flags >> 15 ) & 1 );
    dontAdvance = (FT_UShort)( ( flags >> 14 ) & 1 );
    markLast    = (FT_UShort)( ( flags >> 13 ) & 1 );

    reserved = (FT_UShort)( flags & 0x1FF0 );
    verb     = (FT_UShort)( flags & 0x000F );

    GXV_TRACE(( "  IndicScript MorphRule for glyphOffset 0x%04x",
                glyphOffset_p->u ));
    GXV_TRACE(( " markFirst=%01d", markFirst ));
    GXV_TRACE(( " dontAdvance=%01d", dontAdvance ));
    GXV_TRACE(( " markLast=%01d", markLast ));
    GXV_TRACE(( " %02d", verb ));
    GXV_TRACE(( " %s\n", GXV_Mort_IndicScript_Msg[verb] ));

    if ( markFirst > 0 && markLast > 0 )
    {
      GXV_TRACE(( "  [odd] a glyph is marked as the first and last"
                  "  in Indic rearrangement\n" ));
      GXV_SET_ERR_IF_PARANOID( FT_INVALID_DATA );
    }

    if ( markFirst > 0 && dontAdvance > 0 )
    {
      GXV_TRACE(( "  [odd] the first glyph is marked as dontAdvance"
                  " in Indic rearrangement\n" ));
      GXV_SET_ERR_IF_PARANOID( FT_INVALID_DATA );
    }

    if ( 0 < reserved )
    {
      GXV_TRACE(( " non-zero bits found in reserved range\n" ));
      GXV_SET_ERR_IF_PARANOID( FT_INVALID_DATA );
    }
    else
      GXV_TRACE(( "\n" ));
  }