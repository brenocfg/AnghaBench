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
 int SetIntAndUpdateVideo (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VIDEOMODE_keep_aspect ; 

int VIDEOMODE_SetKeepAspect(int value)
{
	return SetIntAndUpdateVideo(&VIDEOMODE_keep_aspect, value);
}