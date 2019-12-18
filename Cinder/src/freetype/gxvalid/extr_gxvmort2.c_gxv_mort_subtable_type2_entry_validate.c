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
typedef  int /*<<< orphan*/  GXV_Validator ;
typedef  int /*<<< orphan*/  GXV_StateTable_GlyphOffsetCPtr ;
typedef  int FT_UShort ;
typedef  int /*<<< orphan*/  FT_Bytes ;
typedef  int /*<<< orphan*/  FT_Byte ;

/* Variables and functions */
 int /*<<< orphan*/  FT_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxv_mort_subtable_type2_ligActionOffset_validate (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  gxv_mort_subtable_type2_entry_validate(
    FT_Byte                         state,
    FT_UShort                       flags,
    GXV_StateTable_GlyphOffsetCPtr  glyphOffset_p,
    FT_Bytes                        table,
    FT_Bytes                        limit,
    GXV_Validator                   gxvalid )
  {
#ifdef GXV_LOAD_UNUSED_VARS
    FT_UShort setComponent;
    FT_UShort dontAdvance;
#endif
    FT_UShort offset;

    FT_UNUSED( state );
    FT_UNUSED( glyphOffset_p );
    FT_UNUSED( limit );


#ifdef GXV_LOAD_UNUSED_VARS
    setComponent = (FT_UShort)( ( flags >> 15 ) & 1 );
    dontAdvance  = (FT_UShort)( ( flags >> 14 ) & 1 );
#endif

    offset = (FT_UShort)( flags & 0x3FFFU );

    if ( 0 < offset )
      gxv_mort_subtable_type2_ligActionOffset_validate( table, offset,
                                                        gxvalid );
  }