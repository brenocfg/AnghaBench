#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  optdata; } ;
struct TYPE_7__ {TYPE_1__ statetable; } ;
struct TYPE_6__ {int valueTable; int valueTable_length; } ;
typedef  TYPE_2__* GXV_kern_fmt1_StateOptRecData ;
typedef  TYPE_3__* GXV_Validator ;
typedef  int /*<<< orphan*/  GXV_StateTable_GlyphOffsetCPtr ;
typedef  int FT_UShort ;
typedef  int FT_Bytes ;
typedef  int /*<<< orphan*/  FT_Byte ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_OFFSET ; 
 int FT_NEXT_USHORT (int) ; 
 int /*<<< orphan*/  FT_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 

__attribute__((used)) static void
  gxv_kern_subtable_fmt1_entry_validate(
    FT_Byte                         state,
    FT_UShort                       flags,
    GXV_StateTable_GlyphOffsetCPtr  glyphOffset_p,
    FT_Bytes                        table,
    FT_Bytes                        limit,
    GXV_Validator                   gxvalid )
  {
#ifdef GXV_LOAD_UNUSED_VARS
    FT_UShort  push;
    FT_UShort  dontAdvance;
#endif
    FT_UShort  valueOffset;
#ifdef GXV_LOAD_UNUSED_VARS
    FT_UShort  kernAction;
    FT_UShort  kernValue;
#endif

    FT_UNUSED( state );
    FT_UNUSED( glyphOffset_p );


#ifdef GXV_LOAD_UNUSED_VARS
    push        = (FT_UShort)( ( flags >> 15 ) & 1      );
    dontAdvance = (FT_UShort)( ( flags >> 14 ) & 1      );
#endif
    valueOffset = (FT_UShort)(   flags         & 0x3FFF );

    {
      GXV_kern_fmt1_StateOptRecData  vt_rec =
        (GXV_kern_fmt1_StateOptRecData)gxvalid->statetable.optdata;
      FT_Bytes  p;


      if ( valueOffset < vt_rec->valueTable )
        FT_INVALID_OFFSET;

      p     = table + valueOffset;
      limit = table + vt_rec->valueTable + vt_rec->valueTable_length;

      GXV_LIMIT_CHECK( 2 + 2 );
#ifdef GXV_LOAD_UNUSED_VARS
      kernAction = FT_NEXT_USHORT( p );
      kernValue  = FT_NEXT_USHORT( p );
#endif
    }
  }