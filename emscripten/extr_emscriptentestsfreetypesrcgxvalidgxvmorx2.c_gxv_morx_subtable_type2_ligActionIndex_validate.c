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
struct TYPE_7__ {TYPE_1__ xstatetable; } ;
struct TYPE_6__ {scalar_t__ ligActionTable; } ;
typedef  TYPE_2__* GXV_morx_subtable_type2_StateOptRecData ;
typedef  TYPE_3__* GXV_Validator ;
typedef  int FT_UShort ;
typedef  int FT_ULong ;
typedef  scalar_t__ FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_OFFSET ; 
 int FT_NEXT_ULONG (scalar_t__) ; 
 int GXV_MORX_LIGACTION_ENTRY_SIZE ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 

__attribute__((used)) static void
  gxv_morx_subtable_type2_ligActionIndex_validate(
    FT_Bytes       table,
    FT_UShort      ligActionIndex,
    GXV_Validator  valid )
  {
    /* access ligActionTable */
    GXV_morx_subtable_type2_StateOptRecData optdata =
      (GXV_morx_subtable_type2_StateOptRecData)valid->xstatetable.optdata;

    FT_Bytes lat_base  = table + optdata->ligActionTable;
    FT_Bytes p         = lat_base +
                         ligActionIndex * GXV_MORX_LIGACTION_ENTRY_SIZE;
    FT_Bytes lat_limit = lat_base + optdata->ligActionTable;


    if ( p < lat_base )
    {
      GXV_TRACE(( "p < lat_base (%d byte rewind)\n", lat_base - p ));
      FT_INVALID_OFFSET;
    }
    else if ( lat_limit < p )
    {
      GXV_TRACE(( "lat_limit < p (%d byte overrun)\n", p - lat_limit ));
      FT_INVALID_OFFSET;
    }

    {
      /* validate entry in ligActionTable */
      FT_ULong   lig_action;
      FT_UShort  last;
      FT_UShort  store;
      FT_ULong   offset;


      lig_action = FT_NEXT_ULONG( p );
      last       = (FT_UShort)( ( lig_action >> 31 ) & 1 );
      store      = (FT_UShort)( ( lig_action >> 30 ) & 1 );

      offset = lig_action & 0x3FFFFFFFUL;
    }
  }