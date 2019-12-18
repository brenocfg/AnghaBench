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
typedef  int GXV_Validator ;
typedef  int GXV_StateTable_GlyphOffsetCPtr ;
typedef  int FT_UShort ;
typedef  int FT_Bytes ;
typedef  int FT_Byte ;

/* Variables and functions */
 int /*<<< orphan*/  FT_UNUSED (int) ; 

__attribute__((used)) static void
  gxv_just_classTable_entry_validate(
    FT_Byte                         state,
    FT_UShort                       flags,
    GXV_StateTable_GlyphOffsetCPtr  glyphOffset_p,
    FT_Bytes                        table,
    FT_Bytes                        limit,
    GXV_Validator                   gxvalid )
  {
#ifdef GXV_LOAD_UNUSED_VARS
    /* TODO: validate markClass & currentClass */
    FT_UShort  setMark;
    FT_UShort  dontAdvance;
    FT_UShort  markClass;
    FT_UShort  currentClass;
#endif

    FT_UNUSED( state );
    FT_UNUSED( glyphOffset_p );
    FT_UNUSED( table );
    FT_UNUSED( limit );
    FT_UNUSED( gxvalid );

#ifndef GXV_LOAD_UNUSED_VARS
    FT_UNUSED( flags );
#else
    setMark      = (FT_UShort)( ( flags >> 15 ) & 1    );
    dontAdvance  = (FT_UShort)( ( flags >> 14 ) & 1    );
    markClass    = (FT_UShort)( ( flags >> 7  ) & 0x7F );
    currentClass = (FT_UShort)(   flags         & 0x7F );
#endif
  }