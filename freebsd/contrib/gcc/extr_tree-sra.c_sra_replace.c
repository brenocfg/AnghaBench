#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_8__ {int /*<<< orphan*/  bb; } ;
typedef  TYPE_1__ block_stmt_iterator ;

/* Variables and functions */
 scalar_t__ bsi_end_p (TYPE_1__) ; 
 TYPE_1__ bsi_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_prev (TYPE_1__*) ; 
 int /*<<< orphan*/  bsi_remove (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sra_insert_before (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sra_replace (block_stmt_iterator *bsi, tree list)
{
  sra_insert_before (bsi, list);
  bsi_remove (bsi, false);
  if (bsi_end_p (*bsi))
    *bsi = bsi_last (bsi->bb);
  else
    bsi_prev (bsi);
}