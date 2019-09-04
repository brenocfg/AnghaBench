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
struct TYPE_2__ {scalar_t__ fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__ server ; 

void finish(int result) {
  if (server.fd) {
    close(server.fd);
    server.fd = 0;
  }
#ifdef __EMSCRIPTEN__
#ifdef REPORT_RESULT
  REPORT_RESULT(result);
#endif
  emscripten_force_exit(result);
#else
  exit(result);
#endif
}