#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; } ;
typedef  TYPE_1__ main_args ;

/* Variables and functions */
 scalar_t__ __call_main (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_thread_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pthread_self () ; 

void *__emscripten_thread_main(void *param)
{
  emscripten_set_thread_name(pthread_self(), "Application main thread"); // This is the main runtime thread for the application.
  main_args *args = (main_args*)param;
  return (void*)__call_main(args->argc, args->argv);
}