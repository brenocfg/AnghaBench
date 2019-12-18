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
 unsigned int ARRAY_SIZE (char const**) ; 
 char const** __wlp_assc_error ; 

__attribute__((used)) static const char *wlp_assc_error_str(unsigned id)
{
	if (id >= ARRAY_SIZE(__wlp_assc_error))
		return "unknown WLP association error";
	return __wlp_assc_error[id];
}