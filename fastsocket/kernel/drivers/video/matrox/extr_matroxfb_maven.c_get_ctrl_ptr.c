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
struct maven_data {scalar_t__ primary_head; } ;
struct TYPE_2__ {int control; } ;

/* Variables and functions */
 TYPE_1__* maven_controls ; 

__attribute__((used)) static int* get_ctrl_ptr(struct maven_data* md, int idx) {
	return (int*)((char*)(md->primary_head) + maven_controls[idx].control);
}