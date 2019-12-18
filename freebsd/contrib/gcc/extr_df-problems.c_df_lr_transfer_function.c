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
struct df_lr_bb_info {int /*<<< orphan*/  def; int /*<<< orphan*/  use; int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct dataflow {int dummy; } ;
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 int bitmap_ior_and_compl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct df_lr_bb_info* df_lr_get_bb_info (struct dataflow*,int) ; 

__attribute__((used)) static bool
df_lr_transfer_function (struct dataflow *dflow, int bb_index)
{
  struct df_lr_bb_info *bb_info = df_lr_get_bb_info (dflow, bb_index);
  bitmap in = bb_info->in;
  bitmap out = bb_info->out;
  bitmap use = bb_info->use;
  bitmap def = bb_info->def;

  return bitmap_ior_and_compl (in, use, out, def);
}