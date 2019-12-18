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
struct TYPE_2__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct lis3lv02d {int (* read_data ) (struct lis3lv02d*,int /*<<< orphan*/ ) ;TYPE_1__ ac; } ;

/* Variables and functions */
 int /*<<< orphan*/  OUTX ; 
 int /*<<< orphan*/  OUTY ; 
 int /*<<< orphan*/  OUTZ ; 
 int lis3lv02d_get_axis (int /*<<< orphan*/ ,int*) ; 
 int stub1 (struct lis3lv02d*,int /*<<< orphan*/ ) ; 
 int stub2 (struct lis3lv02d*,int /*<<< orphan*/ ) ; 
 int stub3 (struct lis3lv02d*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lis3lv02d_get_xyz(struct lis3lv02d *lis3, int *x, int *y, int *z)
{
	int position[3];

	position[0] = lis3->read_data(lis3, OUTX);
	position[1] = lis3->read_data(lis3, OUTY);
	position[2] = lis3->read_data(lis3, OUTZ);

	*x = lis3lv02d_get_axis(lis3->ac.x, position);
	*y = lis3lv02d_get_axis(lis3->ac.y, position);
	*z = lis3lv02d_get_axis(lis3->ac.z, position);
}