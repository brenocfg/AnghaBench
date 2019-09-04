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
typedef  int UINT ;

/* Variables and functions */
 int eraser_check_interval ; 

UINT GetEraserCheckInterval()
{
	UINT ret = eraser_check_interval / 1000;

	if (ret == 0)
	{
		ret = 1;
	}

	return ret;
}