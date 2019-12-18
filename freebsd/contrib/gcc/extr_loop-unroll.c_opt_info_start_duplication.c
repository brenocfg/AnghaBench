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
struct opt_info {int /*<<< orphan*/  first_new_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  last_basic_block ; 

__attribute__((used)) static void 
opt_info_start_duplication (struct opt_info *opt_info)
{
  if (opt_info)
    opt_info->first_new_block = last_basic_block;
}