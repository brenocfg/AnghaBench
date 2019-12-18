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
 int /*<<< orphan*/  _vita2d_context ; 
 scalar_t__ drawing ; 
 int /*<<< orphan*/  sceGxmEndScene (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void vita2d_end_drawing()
{
	sceGxmEndScene(_vita2d_context, NULL, NULL);
	drawing = 0;
}