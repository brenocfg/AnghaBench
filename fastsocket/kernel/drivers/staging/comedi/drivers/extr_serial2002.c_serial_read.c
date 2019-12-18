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
struct serial_data {int index; int value; void* kind; } ;
struct file {int dummy; } ;

/* Variables and functions */
 void* is_channel ; 
 void* is_digital ; 
 void* is_invalid ; 
 int /*<<< orphan*/  printk (char*) ; 
 int tty_read (struct file*,int) ; 

__attribute__((used)) static struct serial_data serial_read(struct file *f, int timeout)
{
	struct serial_data result;
	int length;

	result.kind = is_invalid;
	result.index = 0;
	result.value = 0;
	length = 0;
	while (1) {
		int data = tty_read(f, timeout);

		length++;
		if (data < 0) {
			printk("serial2002 error\n");
			break;
		} else if (data & 0x80) {
			result.value = (result.value << 7) | (data & 0x7f);
		} else {
			if (length == 1) {
				switch ((data >> 5) & 0x03) {
				case 0:{
						result.value = 0;
						result.kind = is_digital;
					}
					break;
				case 1:{
						result.value = 1;
						result.kind = is_digital;
					}
					break;
				}
			} else {
				result.value =
				    (result.value << 2) | ((data & 0x60) >> 5);
				result.kind = is_channel;
			}
			result.index = data & 0x1f;
			break;
		}
	}
	return result;

}