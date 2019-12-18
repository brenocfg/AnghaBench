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

/* Variables and functions */
 int /*<<< orphan*/  HDAPS_PORT_XPOS ; 
 int /*<<< orphan*/  HDAPS_PORT_YPOS ; 
 int /*<<< orphan*/  __hdaps_read_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rest_x ; 
 int /*<<< orphan*/  rest_y ; 

__attribute__((used)) static void hdaps_calibrate(void)
{
	__hdaps_read_pair(HDAPS_PORT_XPOS, HDAPS_PORT_YPOS, &rest_x, &rest_y);
}