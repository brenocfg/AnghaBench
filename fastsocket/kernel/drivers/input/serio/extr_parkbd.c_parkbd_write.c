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
struct serio {int dummy; } ;

/* Variables and functions */
 unsigned char parkbd_buffer ; 
 scalar_t__ parkbd_counter ; 
 int /*<<< orphan*/  parkbd_mode ; 
 int /*<<< orphan*/  parkbd_writelines (int) ; 
 int parkbd_writing ; 

__attribute__((used)) static int parkbd_write(struct serio *port, unsigned char c)
{
	unsigned char p;

	if (!parkbd_mode) return -1;

        p = c ^ (c >> 4);
	p = p ^ (p >> 2);
	p = p ^ (p >> 1);

	parkbd_counter = 0;
	parkbd_writing = 1;
	parkbd_buffer = c | (((int) (~p & 1)) << 8) | 0x600;

	parkbd_writelines(2);

	return 0;
}