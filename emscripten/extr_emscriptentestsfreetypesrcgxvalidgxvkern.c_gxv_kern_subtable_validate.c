#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int subtable_length; } ;
typedef  TYPE_1__* GXV_Validator ;
typedef  int FT_UShort ;
typedef  int FT_ULong ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_DATA ; 
 int FT_NEXT_USHORT (int) ; 
 int /*<<< orphan*/  GXV_EXIT ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 
#define  KERN_DIALECT_APPLE 129 
#define  KERN_DIALECT_MS 128 
 int /*<<< orphan*/  KERN_IS_NEW (TYPE_1__*) ; 
 int gxv_kern_coverage_validate (int,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  gxv_kern_subtable_fmt0_validate (int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  gxv_kern_subtable_fmt1_validate (int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  gxv_kern_subtable_fmt2_validate (int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  gxv_kern_subtable_fmt3_validate (int,int,TYPE_1__*) ; 

__attribute__((used)) static void
  gxv_kern_subtable_validate( FT_Bytes       table,
                              FT_Bytes       limit,
                              GXV_Validator  valid )
  {
    FT_Bytes   p = table;
    FT_UShort  version = 0;    /* MS only: subtable version, unused */
    FT_ULong   length;         /* MS: 16bit, Apple: 32bit*/
    FT_UShort  coverage;
    FT_UShort  tupleIndex = 0; /* Apple only */
    FT_UShort  u16[2];
    FT_UShort  format = 255;   /* subtable format */


    GXV_NAME_ENTER( "kern subtable" );

    GXV_LIMIT_CHECK( 2 + 2 + 2 );
    u16[0]   = FT_NEXT_USHORT( p ); /* Apple: length_hi MS: version */
    u16[1]   = FT_NEXT_USHORT( p ); /* Apple: length_lo MS: length */
    coverage = FT_NEXT_USHORT( p );

    switch ( gxv_kern_coverage_validate( coverage, &format, valid ) )
    {
    case KERN_DIALECT_MS:
      version    = u16[0];
      length     = u16[1];
      tupleIndex = 0;
      GXV_TRACE(( "Subtable version = %d\n", version ));
      GXV_TRACE(( "Subtable length = %d\n", length ));
      break;

    case KERN_DIALECT_APPLE:
      version    = 0;
      length     = ( u16[0] << 16 ) + u16[1];
      tupleIndex = 0;
      GXV_TRACE(( "Subtable length = %d\n", length ));

      if ( KERN_IS_NEW( valid ) )
      {
        GXV_LIMIT_CHECK( 2 );
        tupleIndex = FT_NEXT_USHORT( p );
        GXV_TRACE(( "Subtable tupleIndex = %d\n", tupleIndex ));
      }
      break;

    default:
      length = u16[1];
      GXV_TRACE(( "cannot detect subtable dialect, "
                  "just skip %d byte\n", length ));
      goto Exit;
    }

    /* formats 1, 2, 3 require the position of the start of this subtable */
    if ( format == 0 )
      gxv_kern_subtable_fmt0_validate( table, table + length, valid );
    else if ( format == 1 )
      gxv_kern_subtable_fmt1_validate( table, table + length, valid );
    else if ( format == 2 )
      gxv_kern_subtable_fmt2_validate( table, table + length, valid );
    else if ( format == 3 )
      gxv_kern_subtable_fmt3_validate( table, table + length, valid );
    else
      FT_INVALID_DATA;

  Exit:
    valid->subtable_length = length;
    GXV_EXIT;
  }