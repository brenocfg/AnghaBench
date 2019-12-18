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
struct loop {int dummy; } ;
typedef  int /*<<< orphan*/  htab_t ;

/* Variables and functions */
 int /*<<< orphan*/  FOLD_CONVERSIONS ; 
 int /*<<< orphan*/  del_scev_info ; 
 int /*<<< orphan*/  eq_scev_info ; 
 int /*<<< orphan*/  hash_scev_info ; 
 int /*<<< orphan*/  htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instantiate_parameters_1 (struct loop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
resolve_mixers (struct loop *loop, tree chrec)
{
  htab_t cache = htab_create (10, hash_scev_info, eq_scev_info, del_scev_info);
  tree ret = instantiate_parameters_1 (loop, chrec, FOLD_CONVERSIONS, cache, 0);
  htab_delete (cache);
  return ret;
}