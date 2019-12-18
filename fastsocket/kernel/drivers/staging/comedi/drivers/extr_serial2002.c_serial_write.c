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
struct serial_data {scalar_t__ kind; int value; int index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_digital ; 
 int /*<<< orphan*/  tty_write (struct file*,unsigned char*,int) ; 

__attribute__((used)) static void serial_write(struct file *f, struct serial_data data)
{
	if (data.kind == is_digital) {
		unsigned char ch =
		    ((data.value << 5) & 0x20) | (data.index & 0x1f);
		tty_write(f, &ch, 1);
	} else {
		unsigned char ch[6];
		int i = 0;
		if (data.value >= (1L << 30)) {
			ch[i] = 0x80 | ((data.value >> 30) & 0x03);
			i++;
		}
		if (data.value >= (1L << 23)) {
			ch[i] = 0x80 | ((data.value >> 23) & 0x7f);
			i++;
		}
		if (data.value >= (1L << 16)) {
			ch[i] = 0x80 | ((data.value >> 16) & 0x7f);
			i++;
		}
		if (data.value >= (1L << 9)) {
			ch[i] = 0x80 | ((data.value >> 9) & 0x7f);
			i++;
		}
		ch[i] = 0x80 | ((data.value >> 2) & 0x7f);
		i++;
		ch[i] = ((data.value << 5) & 0x60) | (data.index & 0x1f);
		i++;
		tty_write(f, ch, i);
	}
}