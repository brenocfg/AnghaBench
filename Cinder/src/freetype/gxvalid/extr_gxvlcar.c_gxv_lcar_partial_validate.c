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

/* Variables and functions */
 int /*<<< orphan*/  GXV_EXIT ; 
 int GXV_LCAR_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  format ; 
 int /*<<< orphan*/  gxv_ctlPoint_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  gxv_lcar_partial_validate( FT_Short       partial,
                             FT_UShort      glyph,
                             GXV_Validator  gxvalid )
  {
    GXV_NAME_ENTER( "partial" );

    if ( GXV_LCAR_DATA( format ) != 1 )
      goto Exit;

    gxv_ctlPoint_validate( glyph, (FT_UShort)partial, gxvalid );

  Exit:
    GXV_EXIT;
  }