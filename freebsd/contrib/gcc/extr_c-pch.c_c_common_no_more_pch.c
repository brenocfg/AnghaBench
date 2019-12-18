#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * valid_pch; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* gt_pch_use_address ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__* cpp_get_callbacks (int /*<<< orphan*/ ) ; 
 TYPE_1__ host_hooks ; 
 int /*<<< orphan*/  parse_in ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
c_common_no_more_pch (void)
{
  if (cpp_get_callbacks (parse_in)->valid_pch)
    {
      cpp_get_callbacks (parse_in)->valid_pch = NULL;
      host_hooks.gt_pch_use_address (NULL, 0, -1, 0);
    }
}