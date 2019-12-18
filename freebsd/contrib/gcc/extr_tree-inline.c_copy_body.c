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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  gcov_type ;
struct TYPE_4__ {int /*<<< orphan*/  src_fn; } ;
typedef  TYPE_1__ copy_body_data ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_STRUCT_FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTRY_BLOCK_PTR_FOR_FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_cfg_body (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
copy_body (copy_body_data *id, gcov_type count, int frequency,
	   basic_block entry_block_map, basic_block exit_block_map)
{
  tree fndecl = id->src_fn;
  tree body;

  /* If this body has a CFG, walk CFG and copy.  */
  gcc_assert (ENTRY_BLOCK_PTR_FOR_FUNCTION (DECL_STRUCT_FUNCTION (fndecl)));
  body = copy_cfg_body (id, count, frequency, entry_block_map, exit_block_map);

  return body;
}