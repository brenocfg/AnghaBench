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
 scalar_t__ EMSCRIPTEN_RESULT_SUCCESS ; 
 int /*<<< orphan*/  RARCH_ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  dummyErrnoCodes () ; 
 int /*<<< orphan*/  emscripten_fullscreenchange_cb ; 
 int /*<<< orphan*/  emscripten_mainloop ; 
 int /*<<< orphan*/  emscripten_set_canvas_element_size (char*,int,int) ; 
 int /*<<< orphan*/  emscripten_set_element_css_size (char*,double,double) ; 
 scalar_t__ emscripten_set_fullscreenchange_callback (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rarch_main (int,char**,int /*<<< orphan*/ *) ; 

int main(int argc, char *argv[])
{
   EMSCRIPTEN_RESULT r;

   dummyErrnoCodes();

   emscripten_set_canvas_element_size("#canvas", 800, 600);
   emscripten_set_element_css_size("#canvas", 800.0, 600.0);
   emscripten_set_main_loop(emscripten_mainloop, 0, 0);
   rarch_main(argc, argv, NULL);

   r = emscripten_set_fullscreenchange_callback("#document", NULL, false,
      emscripten_fullscreenchange_cb);
   if (r != EMSCRIPTEN_RESULT_SUCCESS)
   {
      RARCH_ERR(
         "[EMSCRIPTEN/CTX] failed to create fullscreen callback: %d\n", r);
   }

   return 0;
}