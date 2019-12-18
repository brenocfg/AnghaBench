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
 int ARRAY_SIZE (unsigned char*) ; 
 unsigned char* funce_type_whitelist ; 

__attribute__((used)) static int cistpl_funce_whitelisted(unsigned char type)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(funce_type_whitelist); i++) {
		if (funce_type_whitelist[i] == type)
			return 1;
	}
	return 0;
}