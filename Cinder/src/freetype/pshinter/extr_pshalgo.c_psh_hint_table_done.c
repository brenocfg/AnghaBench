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
struct TYPE_3__ {int /*<<< orphan*/ * sort_global; scalar_t__ max_hints; scalar_t__ num_hints; int /*<<< orphan*/  hints; int /*<<< orphan*/  sort; int /*<<< orphan*/ * zone; scalar_t__ num_zones; int /*<<< orphan*/  zones; } ;
typedef  TYPE_1__* PSH_Hint_Table ;
typedef  int /*<<< orphan*/  FT_Memory ;

/* Variables and functions */
 int /*<<< orphan*/  FT_FREE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  psh_hint_table_done( PSH_Hint_Table  table,
                       FT_Memory       memory )
  {
    FT_FREE( table->zones );
    table->num_zones = 0;
    table->zone      = NULL;

    FT_FREE( table->sort );
    FT_FREE( table->hints );
    table->num_hints   = 0;
    table->max_hints   = 0;
    table->sort_global = NULL;
  }