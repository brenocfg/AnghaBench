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
 int /*<<< orphan*/  emscripten_throw_string (char*) ; 

int main()
{
	emscripten_throw_string("Hello!");
#ifdef REPORT_RESULT
	REPORT_RESULT(1); // failed
#endif
}