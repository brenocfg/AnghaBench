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
typedef  int __u32 ;
struct TYPE_3__ {int id; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int MAVCTRLS ; 
 TYPE_2__* maven_controls ; 

__attribute__((used)) static int get_ctrl_id(__u32 v4l2_id) {
	int i;

	for (i = 0; i < MAVCTRLS; i++) {
		if (v4l2_id < maven_controls[i].desc.id) {
			if (maven_controls[i].desc.id == 0x08000000) {
				return -EINVAL;
			}
			return -ENOENT;
		}
		if (v4l2_id == maven_controls[i].desc.id) {
			return i;
		}
	}
	return -EINVAL;
}