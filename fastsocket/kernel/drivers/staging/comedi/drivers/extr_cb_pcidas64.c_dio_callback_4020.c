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
 int readw (void*) ; 
 int /*<<< orphan*/  writew (int,void*) ; 

__attribute__((used)) static int dio_callback_4020(int dir, int port, int data, unsigned long iobase)
{
	if (dir) {
		writew(data, (void *)(iobase + 2 * port));
		return 0;
	} else {
		return readw((void *)(iobase + 2 * port));
	}
}