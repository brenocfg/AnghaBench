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
struct scev_info_str {int /*<<< orphan*/  chrec; int /*<<< orphan*/  var; } ;
typedef  scalar_t__ PTR ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 scalar_t__* htab_find_slot (int /*<<< orphan*/ ,struct scev_info_str*,int /*<<< orphan*/ ) ; 
 scalar_t__ new_scev_info_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scalar_evolution_info ; 

__attribute__((used)) static tree *
find_var_scev_info (tree var)
{
  struct scev_info_str *res;
  struct scev_info_str tmp;
  PTR *slot;

  tmp.var = var;
  slot = htab_find_slot (scalar_evolution_info, &tmp, INSERT);

  if (!*slot)
    *slot = new_scev_info_str (var);
  res = (struct scev_info_str *) *slot;

  return &res->chrec;
}