#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int subtable_length; } ;
typedef  TYPE_1__* GXV_Validator ;
typedef  int /*<<< orphan*/  FT_UShort ;
typedef  int FT_ULong ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_DATA ; 
 int FT_NEXT_ULONG (int) ; 
 int /*<<< orphan*/  GXV_EXIT ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  gxv_mort_featurearray_validate (int,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  gxv_morx_subtables_validate (int,int,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
  gxv_morx_chain_validate( FT_Bytes       table,
                           FT_Bytes       limit,
                           GXV_Validator  valid )
  {
    FT_Bytes  p = table;
    FT_ULong  defaultFlags;
    FT_ULong  chainLength;
    FT_ULong  nFeatureFlags;
    FT_ULong  nSubtables;


    GXV_NAME_ENTER( "morx chain header" );

    GXV_LIMIT_CHECK( 4 + 4 + 4 + 4 );
    defaultFlags  = FT_NEXT_ULONG( p );
    chainLength   = FT_NEXT_ULONG( p );
    nFeatureFlags = FT_NEXT_ULONG( p );
    nSubtables    = FT_NEXT_ULONG( p );

    /* feature-array of morx is same with that of mort */
    gxv_mort_featurearray_validate( p, limit, nFeatureFlags, valid );
    p += valid->subtable_length;

    if ( nSubtables >= 0x10000L )
      FT_INVALID_DATA;

    gxv_morx_subtables_validate( p, table + chainLength,
                                 (FT_UShort)nSubtables, valid );

    valid->subtable_length = chainLength;

    GXV_EXIT;
  }