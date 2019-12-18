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
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_2__ {int rts_number; } ;

/* Variables and functions */
 TYPE_1__* BB_INFO (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rpost_cmp (const void *bb1, const void *bb2)
{
  basic_block b1 = *(basic_block *) bb1, b2 = *(basic_block *) bb2;

  return BB_INFO (b2)->rts_number - BB_INFO (b1)->rts_number;
}