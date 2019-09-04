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
typedef  scalar_t__ FT_UShort ;
typedef  int /*<<< orphan*/  FT_Short ;
typedef  int /*<<< orphan*/  FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_DATA ; 
 int /*<<< orphan*/  FT_NEXT_SHORT (int /*<<< orphan*/ ) ; 
 scalar_t__ FT_NEXT_USHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_EXIT ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 
 int /*<<< orphan*/  gxv_glyphid_validate (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  gxv_kern_subtable_fmt0_pairs_validate( FT_Bytes       table,
                                         FT_Bytes       limit,
                                         FT_UShort      nPairs,
                                         GXV_Validator  valid )
  {
    FT_Bytes   p = table;
    FT_UShort  i;

    FT_UShort  last_gid_left  = 0;
    FT_UShort  last_gid_right = 0;

    FT_UNUSED( limit );


    GXV_NAME_ENTER( "kern format 0 pairs" );

    for ( i = 0; i < nPairs; i++ )
    {
      FT_UShort  gid_left;
      FT_UShort  gid_right;
      FT_Short   kernValue;


      /* left */
      gid_left  = FT_NEXT_USHORT( p );
      gxv_glyphid_validate( gid_left, valid );

      /* right */
      gid_right = FT_NEXT_USHORT( p );
      gxv_glyphid_validate( gid_right, valid );

      /* Pairs of left and right GIDs must be unique and sorted. */
      GXV_TRACE(( "left gid = %u, right gid = %u\n", gid_left, gid_right ));
      if ( gid_left == last_gid_left )
      {
        if ( last_gid_right < gid_right )
          last_gid_right = gid_right;
        else
          FT_INVALID_DATA;
      }
      else if ( last_gid_left < gid_left )
      {
        last_gid_left  = gid_left;
        last_gid_right = gid_right;
      }
      else
        FT_INVALID_DATA;

      /* skip the kern value */
      kernValue = FT_NEXT_SHORT( p );
    }

    GXV_EXIT;
  }