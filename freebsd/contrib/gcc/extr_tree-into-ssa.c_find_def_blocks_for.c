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
struct def_blocks_d {int /*<<< orphan*/  var; } ;

/* Variables and functions */
 int /*<<< orphan*/  def_blocks ; 
 scalar_t__ htab_find (int /*<<< orphan*/ ,struct def_blocks_d*) ; 

__attribute__((used)) static inline struct def_blocks_d *
find_def_blocks_for (tree var)
{
  struct def_blocks_d dm;
  dm.var = var;
  return (struct def_blocks_d *) htab_find (def_blocks, &dm);
}