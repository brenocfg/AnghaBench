#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct version_info {TYPE_1__* iv; } ;
struct ivopts_data {int /*<<< orphan*/  relevant; } ;
struct TYPE_2__ {int /*<<< orphan*/  ssa_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 TYPE_1__* alloc_iv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 struct version_info* name_info (struct ivopts_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_iv (struct ivopts_data *data, tree iv, tree base, tree step)
{
  struct version_info *info = name_info (data, iv);

  gcc_assert (!info->iv);

  bitmap_set_bit (data->relevant, SSA_NAME_VERSION (iv));
  info->iv = alloc_iv (base, step);
  info->iv->ssa_name = iv;
}