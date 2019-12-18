#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtx_constant_pool {struct constant_descriptor_rtx* first; } ;
struct constant_descriptor_rtx {int /*<<< orphan*/  align; int /*<<< orphan*/  constant; int /*<<< orphan*/  mode; int /*<<< orphan*/  sym; scalar_t__ mark; struct constant_descriptor_rtx* next; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* select_rtx_section ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ asm_out; } ;

/* Variables and functions */
 scalar_t__ SYMBOL_REF_BLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ SYMBOL_REF_HAS_BLOCK_INFO_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_constant_pool_1 (struct constant_descriptor_rtx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  place_block_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switch_to_section (int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 

__attribute__((used)) static void
output_constant_pool_contents (struct rtx_constant_pool *pool)
{
  struct constant_descriptor_rtx *desc;

  for (desc = pool->first; desc ; desc = desc->next)
    if (desc->mark)
      {
	/* If the constant is part of an object_block, make sure that
	   the constant has been positioned within its block, but do not
	   write out its definition yet.  output_object_blocks will do
	   that later.  */
	if (SYMBOL_REF_HAS_BLOCK_INFO_P (desc->sym)
	    && SYMBOL_REF_BLOCK (desc->sym))
	  place_block_symbol (desc->sym);
	else
	  {
	    switch_to_section (targetm.asm_out.select_rtx_section
			       (desc->mode, desc->constant, desc->align));
	    output_constant_pool_1 (desc, desc->align);
	  }
      }
}