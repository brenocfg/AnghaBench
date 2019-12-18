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
struct lis3lv02d {scalar_t__ (* read ) (struct lis3lv02d*,int,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 scalar_t__ stub1 (struct lis3lv02d*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s16 lis3lv02d_read_8(struct lis3lv02d *lis3, int reg)
{
	s8 lo;
	if (lis3->read(lis3, reg, &lo) < 0)
		return 0;

	return lo;
}