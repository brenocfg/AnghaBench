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
 int /*<<< orphan*/  HOST_CTRL_IO (unsigned int) ; 
 int /*<<< orphan*/  HOST_DATA_IO (unsigned int) ; 
 int TX_READY ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int host_write_unsafe(unsigned io_base, unsigned char data)
{
	if ((inb(HOST_CTRL_IO(io_base)) & TX_READY) != 0) {
		outb(data, HOST_DATA_IO(io_base));
		return 1;
	}

	return 0;
}