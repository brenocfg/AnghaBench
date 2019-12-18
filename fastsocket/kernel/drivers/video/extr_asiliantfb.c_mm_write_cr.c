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
typedef  int /*<<< orphan*/  u8 ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mm_write_ind (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void mm_write_cr(struct fb_info *p, u8 reg, u8 data)
{
	mm_write_ind(reg, data, 0x7a8, 0x7a9);
}