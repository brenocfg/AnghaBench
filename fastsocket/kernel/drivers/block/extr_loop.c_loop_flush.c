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
struct loop_device {int /*<<< orphan*/  lo_thread; } ;

/* Variables and functions */
 int loop_switch (struct loop_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int loop_flush(struct loop_device *lo)
{
	/* loop not yet configured, no running thread, nothing to flush */
	if (!lo->lo_thread)
		return 0;

	return loop_switch(lo, NULL);
}