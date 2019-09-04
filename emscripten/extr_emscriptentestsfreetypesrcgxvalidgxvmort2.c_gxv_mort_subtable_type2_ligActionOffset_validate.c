#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  optdata; } ;
struct TYPE_9__ {TYPE_2__* root; TYPE_1__ statetable; } ;
struct TYPE_8__ {scalar_t__ ligActionTable; } ;
struct TYPE_7__ {scalar_t__ level; } ;
typedef  TYPE_3__* GXV_mort_subtable_type2_StateOptRecData ;
typedef  TYPE_4__* GXV_Validator ;
typedef  scalar_t__ FT_UShort ;
typedef  int FT_ULong ;
typedef  scalar_t__ FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_OFFSET ; 
 int FT_NEXT_ULONG (scalar_t__) ; 
 scalar_t__ FT_VALIDATE_PARANOID ; 
 int /*<<< orphan*/  GXV_32BIT_ALIGNMENT_VALIDATE (scalar_t__) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 

__attribute__((used)) static void
  gxv_mort_subtable_type2_ligActionOffset_validate(
    FT_Bytes       table,
    FT_UShort      ligActionOffset,
    GXV_Validator  valid )
  {
    /* access ligActionTable */
    GXV_mort_subtable_type2_StateOptRecData  optdata =
      (GXV_mort_subtable_type2_StateOptRecData)valid->statetable.optdata;

    FT_Bytes lat_base  = table + optdata->ligActionTable;
    FT_Bytes p         = table + ligActionOffset;
    FT_Bytes lat_limit = lat_base + optdata->ligActionTable;


    GXV_32BIT_ALIGNMENT_VALIDATE( ligActionOffset );
    if ( p < lat_base )
    {
      GXV_TRACE(( "too short offset 0x%04x: p < lat_base (%d byte rewind)\n",
                  ligActionOffset, lat_base - p ));

      /* FontValidator, ftxvalidator, ftxdumperfuser warn but continue */
      if ( valid->root->level >= FT_VALIDATE_PARANOID )
        FT_INVALID_OFFSET;
    }
    else if ( lat_limit < p )
    {
      GXV_TRACE(( "too large offset 0x%04x: lat_limit < p (%d byte overrun)\n",
                  ligActionOffset, p - lat_limit ));

      /* FontValidator, ftxvalidator, ftxdumperfuser warn but continue */
      if ( valid->root->level >= FT_VALIDATE_PARANOID )
        FT_INVALID_OFFSET;
    }
    else
    {
      /* validate entry in ligActionTable */
      FT_ULong   lig_action;
      FT_UShort  last;
      FT_UShort  store;
      FT_ULong   offset;


      lig_action = FT_NEXT_ULONG( p );
      last   = (FT_UShort)( ( lig_action >> 31 ) & 1 );
      store  = (FT_UShort)( ( lig_action >> 30 ) & 1 );

      offset = lig_action & 0x3FFFFFFFUL;
    }
  }