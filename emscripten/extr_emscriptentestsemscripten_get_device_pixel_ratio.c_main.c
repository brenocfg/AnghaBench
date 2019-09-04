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
 double emscripten_get_device_pixel_ratio () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main()
{
	double devicePixelRatio = emscripten_get_device_pixel_ratio();
	printf("window.devicePixelRatio = %f.\n", devicePixelRatio);
	int result = (devicePixelRatio > 0) ? 1 : 0;
	if (result) {
		printf("Test succeeded!\n");
	}
#ifdef REPORT_RESULT
	REPORT_RESULT(result);
#endif
}