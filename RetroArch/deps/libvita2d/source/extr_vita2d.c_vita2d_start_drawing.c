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
 int /*<<< orphan*/  vita2d_pool_reset () ; 
 int /*<<< orphan*/  vita2d_start_drawing_advanced (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void vita2d_start_drawing()
{
	vita2d_pool_reset();
	vita2d_start_drawing_advanced(NULL, 0);
}