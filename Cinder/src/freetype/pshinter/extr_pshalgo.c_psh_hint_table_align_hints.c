#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  scale_delta; int /*<<< orphan*/  scale_mult; } ;
struct TYPE_9__ {TYPE_3__* dimension; } ;
struct TYPE_8__ {scalar_t__ max_hints; int /*<<< orphan*/  hints; } ;
typedef  TYPE_1__* PSH_Hint_Table ;
typedef  int /*<<< orphan*/  PSH_Hint ;
typedef  int /*<<< orphan*/  PSH_Glyph ;
typedef  TYPE_2__* PSH_Globals ;
typedef  TYPE_3__* PSH_Dimension ;
typedef  scalar_t__ FT_UInt ;
typedef  size_t FT_Int ;
typedef  int /*<<< orphan*/  FT_Fixed ;

/* Variables and functions */
 scalar_t__ ps_debug_no_horz_hints ; 
 scalar_t__ ps_debug_no_vert_hints ; 
 int /*<<< orphan*/  ps_simple_scale (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  psh_hint_align (int /*<<< orphan*/ ,TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  psh_hint_table_align_hints( PSH_Hint_Table  table,
                              PSH_Globals     globals,
                              FT_Int          dimension,
                              PSH_Glyph       glyph )
  {
    PSH_Hint       hint;
    FT_UInt        count;

#ifdef DEBUG_HINTER

    PSH_Dimension  dim   = &globals->dimension[dimension];
    FT_Fixed       scale = dim->scale_mult;
    FT_Fixed       delta = dim->scale_delta;


    if ( ps_debug_no_vert_hints && dimension == 0 )
    {
      ps_simple_scale( table, scale, delta, dimension );
      return;
    }

    if ( ps_debug_no_horz_hints && dimension == 1 )
    {
      ps_simple_scale( table, scale, delta, dimension );
      return;
    }

#endif /* DEBUG_HINTER*/

    hint  = table->hints;
    count = table->max_hints;

    for ( ; count > 0; count--, hint++ )
      psh_hint_align( hint, globals, dimension, glyph );
  }