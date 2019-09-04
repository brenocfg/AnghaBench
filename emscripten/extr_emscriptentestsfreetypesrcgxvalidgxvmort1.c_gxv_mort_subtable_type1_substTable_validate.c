#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ optdata; } ;
struct TYPE_11__ {TYPE_2__* root; TYPE_1__* face; TYPE_3__ statetable; } ;
struct TYPE_10__ {int substitutionTable_length; } ;
struct TYPE_8__ {scalar_t__ level; } ;
struct TYPE_7__ {scalar_t__ num_glyphs; } ;
typedef  TYPE_4__ GXV_mort_subtable_type1_StateOptRec ;
typedef  TYPE_5__* GXV_Validator ;
typedef  scalar_t__ FT_UShort ;
typedef  int /*<<< orphan*/  FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_GLYPH_ID ; 
 scalar_t__ FT_NEXT_USHORT (int /*<<< orphan*/ ) ; 
 scalar_t__ FT_VALIDATE_PARANOID ; 
 int /*<<< orphan*/  GXV_EXIT ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 

__attribute__((used)) static void
  gxv_mort_subtable_type1_substTable_validate( FT_Bytes       table,
                                               FT_Bytes       limit,
                                               GXV_Validator  valid )
  {
    FT_Bytes   p = table;
    FT_UShort  num_gids = (FT_UShort)(
                 ((GXV_mort_subtable_type1_StateOptRec *)
                  (valid->statetable.optdata))->substitutionTable_length / 2 );
    FT_UShort  i;


    GXV_NAME_ENTER( "validating contents of substitutionTable" );
    for ( i = 0; i < num_gids ; i ++ )
    {
      FT_UShort  dst_gid;


      GXV_LIMIT_CHECK( 2 );
      dst_gid = FT_NEXT_USHORT( p );

      if ( dst_gid >= 0xFFFFU )
        continue;

      if ( dst_gid > valid->face->num_glyphs )
      {
        GXV_TRACE(( "substTable include too large gid[%d]=%d >"
                    " max defined gid #%d\n",
                    i, dst_gid, valid->face->num_glyphs ));
        if ( valid->root->level >= FT_VALIDATE_PARANOID )
          FT_INVALID_GLYPH_ID;
      }
    }

    GXV_EXIT;
  }