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
struct device_path {int* layers; } ;
struct pdcspath_entry {short ready; int /*<<< orphan*/  rw_lock; struct device_path devpath; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t
pdcspath_layer_read(struct pdcspath_entry *entry, char *buf)
{
	char *out = buf;
	struct device_path *devpath;
	short i;

	if (!entry || !buf)
		return -EINVAL;
	
	read_lock(&entry->rw_lock);
	devpath = &entry->devpath;
	i = entry->ready;
	read_unlock(&entry->rw_lock);

	if (!i)	/* entry is not ready */
		return -ENODATA;
	
	for (i = 0; i < 6 && devpath->layers[i]; i++)
		out += sprintf(out, "%u ", devpath->layers[i]);

	out += sprintf(out, "\n");
	
	return out - buf;
}