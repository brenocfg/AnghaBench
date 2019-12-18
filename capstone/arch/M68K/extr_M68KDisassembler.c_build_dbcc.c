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
struct TYPE_4__ {int ir; } ;
typedef  TYPE_1__ m68k_info ;

/* Variables and functions */
 int /*<<< orphan*/  build_dbxx (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * s_dbcc_lut ; 

__attribute__((used)) static void build_dbcc(m68k_info *info, int size, int displacement)
{
	build_dbxx(info, s_dbcc_lut[(info->ir >> 8) & 0xf], size, displacement);
}