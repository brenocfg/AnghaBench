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
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int InternalLoad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wgl_CopyFromC () ; 

int wgl_LoadFunctions(HDC hdc)
{
	int numFailed = 0;
	numFailed = InternalLoad(hdc);
	wgl_CopyFromC();
	return numFailed;
}