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
typedef  int /*<<< orphan*/  u32 ;
struct kfifo {int dummy; } ;

/* Variables and functions */
 scalar_t__ kfifo_get (struct kfifo*,unsigned char*,int) ; 

__attribute__((used)) static u32 cxio_hal_get_resource(struct kfifo *fifo)
{
	u32 entry;
	if (kfifo_get(fifo, (unsigned char *) &entry, sizeof(u32)))
		return entry;
	else
		return 0;	/* fifo emptry */
}