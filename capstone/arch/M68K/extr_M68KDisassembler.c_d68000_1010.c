#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ir; } ;
typedef  TYPE_1__ m68k_info ;

/* Variables and functions */
 int /*<<< orphan*/  build_invalid (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d68000_1010(m68k_info *info)
{
	build_invalid(info, info->ir);
}