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
 int /*<<< orphan*/  DEBUG_PRINT (char*,int,int) ; 
 int readb (void*) ; 
 int /*<<< orphan*/  writeb (int,void*) ; 

__attribute__((used)) static int dio_callback(int dir, int port, int data, unsigned long iobase)
{
	if (dir) {
		writeb(data, (void *)(iobase + port));
		DEBUG_PRINT("wrote 0x%x to port %i\n", data, port);
		return 0;
	} else {
		return readb((void *)(iobase + port));
	}
}