#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int subtable_length; TYPE_1__* root; } ;
struct TYPE_6__ {int base; } ;
typedef  TYPE_2__* GXV_Validator ;
typedef  int FT_UShort ;
typedef  int FT_ULong ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int FT_NEXT_ULONG (int) ; 
 int FT_NEXT_USHORT (int) ; 
 int /*<<< orphan*/  GXV_EXIT ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  GXV_ODTECT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_ODTECT_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 
 int GXV_TRAK_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxv_odtect_add_range (int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxv_odtect_validate (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  gxv_trak_trackTable_validate (int,int,int,TYPE_2__*) ; 
 int /*<<< orphan*/  odtect ; 
 int /*<<< orphan*/  trackValueOffset_max ; 
 int /*<<< orphan*/  trackValueOffset_min ; 

__attribute__((used)) static void
  gxv_trak_trackData_validate( FT_Bytes       table,
                               FT_Bytes       limit,
                               GXV_Validator  gxvalid )
  {
    FT_Bytes   p = table;
    FT_UShort  nTracks;
    FT_UShort  nSizes;
    FT_ULong   sizeTableOffset;

    GXV_ODTECT( 4, odtect );


    GXV_ODTECT_INIT( odtect );
    GXV_NAME_ENTER( "trackData" );

    /* read the header of trackData */
    GXV_LIMIT_CHECK( 2 + 2 + 4 );
    nTracks         = FT_NEXT_USHORT( p );
    nSizes          = FT_NEXT_USHORT( p );
    sizeTableOffset = FT_NEXT_ULONG( p );

    gxv_odtect_add_range( table, (FT_ULong)( p - table ),
                          "trackData header", odtect );

    /* validate trackTable */
    gxv_trak_trackTable_validate( p, limit, nTracks, gxvalid );
    gxv_odtect_add_range( p, gxvalid->subtable_length,
                          "trackTable", odtect );

    /* sizeTable is array of FT_Fixed, don't check contents */
    p = gxvalid->root->base + sizeTableOffset;
    GXV_LIMIT_CHECK( nSizes * 4 );
    gxv_odtect_add_range( p, nSizes * 4, "sizeTable", odtect );

    /* validate trackValueOffet */
    p = gxvalid->root->base + GXV_TRAK_DATA( trackValueOffset_min );
    if ( limit - p < nTracks * nSizes * 2 )
      GXV_TRACE(( "too short trackValue array\n" ));

    p = gxvalid->root->base + GXV_TRAK_DATA( trackValueOffset_max );
    GXV_LIMIT_CHECK( nSizes * 2 );

    gxv_odtect_add_range( gxvalid->root->base
                            + GXV_TRAK_DATA( trackValueOffset_min ),
                          GXV_TRAK_DATA( trackValueOffset_max )
                            - GXV_TRAK_DATA( trackValueOffset_min )
                            + nSizes * 2,
                          "trackValue array", odtect );

    gxv_odtect_validate( odtect, gxvalid );

    GXV_EXIT;
  }