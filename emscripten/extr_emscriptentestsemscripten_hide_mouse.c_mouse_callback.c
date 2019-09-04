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
typedef  int /*<<< orphan*/  EmscriptenMouseEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

EM_BOOL mouse_callback(int eventType, const EmscriptenMouseEvent *e, void *userData)
{
	printf("Mouse click on canvas.\n");
#ifdef REPORT_RESULT
	REPORT_RESULT(0);
#endif
	return 0;
}