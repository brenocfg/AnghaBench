#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lookup_count; int /*<<< orphan*/  extra1; } ;
typedef  TYPE_1__* OTV_Validator ;
typedef  int FT_UInt ;
typedef  int /*<<< orphan*/  FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  ChainContextPosFormat1 ; 
 int /*<<< orphan*/  ChainContextPosFormat2 ; 
 int /*<<< orphan*/  ChainContextPosFormat3 ; 
 int /*<<< orphan*/  ChainPosClassRule ; 
 int /*<<< orphan*/  ChainPosClassSet ; 
 int /*<<< orphan*/  ChainPosRule ; 
 int /*<<< orphan*/  ChainPosRuleSet ; 
 int /*<<< orphan*/  FT_INVALID_FORMAT ; 
 int FT_NEXT_USHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OTV_EXIT ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  OTV_NEST1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OTV_NEST3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OTV_RUN (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  OTV_TRACE (char*) ; 

__attribute__((used)) static void
  otv_ChainContextPos_validate( FT_Bytes       table,
                                OTV_Validator  otvalid )
  {
    FT_Bytes  p = table;
    FT_UInt   PosFormat;


    OTV_NAME_ENTER( "ChainContextPos" );

    OTV_LIMIT_CHECK( 2 );
    PosFormat = FT_NEXT_USHORT( p );

    OTV_TRACE(( " (format %d)\n", PosFormat ));

    switch ( PosFormat )
    {
    case 1:
      /* no need to check glyph indices/classes used as input for these */
      /* context rules since even invalid glyph indices/classes return  */
      /* meaningful results                                             */

      otvalid->extra1 = otvalid->lookup_count;
      OTV_NEST3( ChainContextPosFormat1,
                 ChainPosRuleSet, ChainPosRule );
      OTV_RUN( table, otvalid );
      break;

    case 2:
      /* no need to check glyph indices/classes used as input for these */
      /* context rules since even invalid glyph indices/classes return  */
      /* meaningful results                                             */

      OTV_NEST3( ChainContextPosFormat2,
                 ChainPosClassSet, ChainPosClassRule );
      OTV_RUN( table, otvalid );
      break;

    case 3:
      OTV_NEST1( ChainContextPosFormat3 );
      OTV_RUN( table, otvalid );
      break;

    default:
      FT_INVALID_FORMAT;
    }

    OTV_EXIT;
  }