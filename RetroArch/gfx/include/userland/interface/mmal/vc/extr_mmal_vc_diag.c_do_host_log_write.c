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
 int /*<<< orphan*/  mmal_vc_host_log (char const*) ; 

__attribute__((used)) static int do_host_log_write(int argc, const char **argv)
{
   if (argc > 2)
      mmal_vc_host_log(argv[2]);
   return 0;
}