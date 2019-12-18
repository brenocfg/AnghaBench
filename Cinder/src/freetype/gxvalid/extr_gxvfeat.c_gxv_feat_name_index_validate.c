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
typedef  int /*<<< orphan*/  FT_UShort ;
typedef  scalar_t__ FT_Short ;
typedef  int /*<<< orphan*/  FT_Bytes ;

/* Variables and functions */
 scalar_t__ FT_NEXT_SHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_EXIT ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 
 int /*<<< orphan*/  gxv_sfntName_validate (int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  gxv_feat_name_index_validate( FT_Bytes       table,
                                FT_Bytes       limit,
                                GXV_Validator  gxvalid )
  {
    FT_Bytes  p = table;

    FT_Short  nameIndex;


    GXV_NAME_ENTER( "nameIndex" );

    GXV_LIMIT_CHECK( 2 );
    nameIndex = FT_NEXT_SHORT ( p );
    GXV_TRACE(( " (nameIndex = %d)\n", nameIndex ));

    gxv_sfntName_validate( (FT_UShort)nameIndex,
                           255,
                           32768U,
                           gxvalid );

    GXV_EXIT;
  }