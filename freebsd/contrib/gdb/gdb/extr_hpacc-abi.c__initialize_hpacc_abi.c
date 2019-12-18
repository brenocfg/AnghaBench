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

/* Variables and functions */
 int /*<<< orphan*/  REG_NOSUB ; 
 int /*<<< orphan*/  constructor_pattern ; 
 int /*<<< orphan*/  destructor_pattern ; 
 int /*<<< orphan*/  hpacc_abi_ops ; 
 int /*<<< orphan*/  init_hpacc_ops () ; 
 int /*<<< orphan*/  operator_pattern ; 
 int /*<<< orphan*/  regcomp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_cp_abi (int /*<<< orphan*/ *) ; 

void
_initialize_hpacc_abi (void)
{
  init_hpacc_ops ();

  regcomp (&constructor_pattern,
	   "^This will never match anything, please fill it in$", REG_NOSUB);

  regcomp (&destructor_pattern,
	   "^This will never match anything, please fill it in$", REG_NOSUB);

  regcomp (&operator_pattern,
	   "^This will never match anything, please fill it in$", REG_NOSUB);

  register_cp_abi (&hpacc_abi_ops);
}