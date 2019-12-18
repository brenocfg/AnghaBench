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
struct acpiphp_attention_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct acpiphp_attention_info* attention_info ; 

int acpiphp_unregister_attention(struct acpiphp_attention_info *info)
{
	int retval = -EINVAL;

	if (info && attention_info == info) {
		attention_info = NULL;
		retval = 0;
	}
	return retval;
}