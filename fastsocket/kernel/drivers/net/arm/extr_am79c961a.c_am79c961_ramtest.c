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
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  am_readbuffer (struct net_device*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  am_writebuffer (struct net_device*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,unsigned int,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int
am79c961_ramtest(struct net_device *dev, unsigned int val)
{
	unsigned char *buffer = kmalloc (65536, GFP_KERNEL);
	int i, error = 0, errorcount = 0;

	if (!buffer)
		return 0;
	memset (buffer, val, 65536);
	am_writebuffer(dev, 0, buffer, 65536);
	memset (buffer, val ^ 255, 65536);
	am_readbuffer(dev, 0, buffer, 65536);
	for (i = 0; i < 65536; i++) {
		if (buffer[i] != val && !error) {
			printk ("%s: buffer error (%02X %02X) %05X - ", dev->name, val, buffer[i], i);
			error = 1;
			errorcount ++;
		} else if (error && buffer[i] == val) {
			printk ("%05X\n", i);
			error = 0;
		}
	}
	if (error)
		printk ("10000\n");
	kfree (buffer);
	return errorcount;
}