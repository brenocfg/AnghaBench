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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  section ;
struct TYPE_3__ {int /*<<< orphan*/ * (* select_section ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ asm_out; } ;

/* Variables and functions */
 scalar_t__ IN_NAMED_SECTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_reloc_for_constant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_constant_alignment (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_named_section (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 

__attribute__((used)) static section *
get_constant_section (tree exp)
{
  if (IN_NAMED_SECTION (exp))
    return get_named_section (exp, NULL, compute_reloc_for_constant (exp));
  else
    return targetm.asm_out.select_section (exp,
					   compute_reloc_for_constant (exp),
					   get_constant_alignment (exp));
}