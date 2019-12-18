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
 int /*<<< orphan*/  resource_alignment_lock ; 
 char* resource_alignment_param ; 
 size_t snprintf (char*,size_t,char*,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

ssize_t pci_get_resource_alignment_param(char *buf, size_t size)
{
	size_t count;
	spin_lock(&resource_alignment_lock);
	count = snprintf(buf, size, "%s", resource_alignment_param);
	spin_unlock(&resource_alignment_lock);
	return count;
}