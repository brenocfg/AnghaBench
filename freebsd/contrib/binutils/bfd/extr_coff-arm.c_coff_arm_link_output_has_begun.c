#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct coff_final_link_info {int /*<<< orphan*/  info; } ;
typedef  int bfd_boolean ;
struct TYPE_4__ {scalar_t__ output_has_begun; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_5__ {TYPE_1__* bfd_of_glue_owner; } ;

/* Variables and functions */
 TYPE_3__* coff_arm_hash_table (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
coff_arm_link_output_has_begun (bfd * sub, struct coff_final_link_info * info)
{
  return (sub->output_has_begun
	  || sub == coff_arm_hash_table (info->info)->bfd_of_glue_owner);
}