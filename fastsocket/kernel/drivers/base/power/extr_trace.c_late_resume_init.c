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
 unsigned int FILEHASH ; 
 unsigned int USERHASH ; 
 unsigned int hash_value_early_read ; 
 int /*<<< orphan*/  printk (char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  show_dev_hash (unsigned int) ; 
 int /*<<< orphan*/  show_file_hash (unsigned int) ; 

__attribute__((used)) static int late_resume_init(void)
{
	unsigned int val = hash_value_early_read;
	unsigned int user, file, dev;

	user = val % USERHASH;
	val = val / USERHASH;
	file = val % FILEHASH;
	val = val / FILEHASH;
	dev = val /* % DEVHASH */;

	printk("  Magic number: %d:%d:%d\n", user, file, dev);
	show_file_hash(file);
	show_dev_hash(dev);
	return 0;
}