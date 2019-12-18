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
typedef  size_t u8 ;

/* Variables and functions */
 char** iwl_dvm_cmd_strings ; 

__attribute__((used)) static inline const char *iwl_dvm_get_cmd_string(u8 cmd)
{
	const char *s = iwl_dvm_cmd_strings[cmd];
	if (s)
		return s;
	return "UNKNOWN";
}