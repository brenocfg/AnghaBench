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
typedef  size_t ssize_t ;

/* Variables and functions */
 int RESOURCE_ALIGNMENT_PARAM_SIZE ; 
 int /*<<< orphan*/  resource_alignment_lock ; 
 char* resource_alignment_param ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

ssize_t pci_set_resource_alignment_param(const char *buf, size_t count)
{
	if (count > RESOURCE_ALIGNMENT_PARAM_SIZE - 1)
		count = RESOURCE_ALIGNMENT_PARAM_SIZE - 1;
	spin_lock(&resource_alignment_lock);
	strncpy(resource_alignment_param, buf, count);
	resource_alignment_param[count] = '\0';
	spin_unlock(&resource_alignment_lock);
	return count;
}