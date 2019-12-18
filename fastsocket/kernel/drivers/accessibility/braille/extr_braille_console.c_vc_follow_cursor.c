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
struct vc_data {int vc_x; int /*<<< orphan*/  vc_y; } ;

/* Variables and functions */
 int WIDTH ; 
 int lastvc_x ; 
 int /*<<< orphan*/  lastvc_y ; 
 int vc_x ; 
 int /*<<< orphan*/  vc_y ; 

__attribute__((used)) static void vc_follow_cursor(struct vc_data *vc)
{
	vc_x = vc->vc_x - (vc->vc_x % WIDTH);
	vc_y = vc->vc_y;
	lastvc_x = vc->vc_x;
	lastvc_y = vc->vc_y;
}