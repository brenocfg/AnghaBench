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
typedef  scalar_t__ EMSCRIPTEN_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EM_ASM (int) ; 
 int* Module ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emscripten_hide_mouse () ; 
 scalar_t__ emscripten_set_click_callback (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mouse_callback ; 
 int /*<<< orphan*/  printf (char*) ; 

int main()
{
	printf("The mouse cursor should be hidden when hovering over the canvas rectangle. Click on the canvas to finish test.\n");
	emscripten_hide_mouse();
	EMSCRIPTEN_RESULT ret = emscripten_set_click_callback("#canvas", 0, 1, mouse_callback);
	assert(ret == 0);
	EM_ASM(Module['noExitRuntime'] = true);
}