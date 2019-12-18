#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * table_data; } ;
typedef  TYPE_1__* GXV_Validator ;
typedef  int /*<<< orphan*/  FT_Bytes ;

/* Variables and functions */
 int GXV_BSLN_VALUE_COUNT ; 
 int /*<<< orphan*/  GXV_EXIT ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 

__attribute__((used)) static void
  gxv_bsln_parts_fmt0_validate( FT_Bytes       tables,
                                FT_Bytes       limit,
                                GXV_Validator  gxvalid )
  {
    FT_Bytes  p = tables;


    GXV_NAME_ENTER( "parts format 0" );

    /* deltas */
    GXV_LIMIT_CHECK( 2 * GXV_BSLN_VALUE_COUNT );

    gxvalid->table_data = NULL;      /* No ctlPoints here. */

    GXV_EXIT;
  }