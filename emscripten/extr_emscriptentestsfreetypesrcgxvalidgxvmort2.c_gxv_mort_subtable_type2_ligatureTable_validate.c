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
struct TYPE_6__ {scalar_t__ ligatureTable; scalar_t__ ligatureTable_length; } ;
typedef  TYPE_2__* GXV_mort_subtable_type2_StateOptRecData ;
typedef  TYPE_3__* GXV_Validator ;
typedef  int /*<<< orphan*/  FT_UShort ;
typedef  scalar_t__ FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_NEXT_USHORT (scalar_t__) ; 
 int /*<<< orphan*/  GXV_EXIT ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 

__attribute__((used)) static void
  gxv_mort_subtable_type2_ligatureTable_validate( FT_Bytes       table,
                                                  GXV_Validator  valid )
  {
    GXV_mort_subtable_type2_StateOptRecData  optdata =
      (GXV_mort_subtable_type2_StateOptRecData)valid->statetable.optdata;

    FT_Bytes p     = table + optdata->ligatureTable;
    FT_Bytes limit = table + optdata->ligatureTable
                           + optdata->ligatureTable_length;


    GXV_NAME_ENTER( "mort chain subtable type2 - substitutionTable" );
    if ( 0 != optdata->ligatureTable )
    {
      /* Apple does not give specification of ligatureTable format */
      while ( p < limit )
      {
        FT_UShort  lig_gid;


        GXV_LIMIT_CHECK( 2 );
        lig_gid = FT_NEXT_USHORT( p );
      }
    }
    GXV_EXIT;
  }