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
struct pt1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt1_i2c_emit (struct pt1*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pt1_i2c_init(struct pt1 *pt1)
{
	int i;
	for (i = 0; i < 1024; i++)
		pt1_i2c_emit(pt1, i, 0, 0, 1, 1, 0);
}