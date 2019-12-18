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
struct opt_info {scalar_t__ insns_with_var_to_expand; scalar_t__ insns_to_split; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct opt_info*) ; 
 int /*<<< orphan*/  htab_delete (scalar_t__) ; 
 int /*<<< orphan*/  htab_traverse (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_var_copies ; 

__attribute__((used)) static void
free_opt_info (struct opt_info *opt_info)
{
  if (opt_info->insns_to_split)
    htab_delete (opt_info->insns_to_split);
  if (opt_info->insns_with_var_to_expand)
    {
      htab_traverse (opt_info->insns_with_var_to_expand, 
                     release_var_copies, NULL);
      htab_delete (opt_info->insns_with_var_to_expand);
    }
  free (opt_info);
}