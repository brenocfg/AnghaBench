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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  dataflow_set ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MEM_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_EXPR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clobber_variable_part (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_debug_decl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_mem_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
var_mem_delete_and_set (dataflow_set *set, rtx loc, bool modify)
{
  tree decl = MEM_EXPR (loc);
  HOST_WIDE_INT offset = INT_MEM_OFFSET (loc);

  decl = var_debug_decl (decl);

  if (modify)
    clobber_variable_part (set, NULL, decl, offset);
  var_mem_set (set, loc);
}