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
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  rtl_create_basic_block (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static basic_block
cfg_layout_create_basic_block (void *head, void *end, basic_block after)
{
  basic_block newbb = rtl_create_basic_block (head, end, after);

  return newbb;
}