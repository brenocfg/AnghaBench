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
struct bus_type {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ap_poll_thread_start () ; 
 int /*<<< orphan*/  ap_poll_thread_stop () ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static ssize_t ap_poll_thread_store(struct bus_type *bus,
				    const char *buf, size_t count)
{
	int flag, rc;

	if (sscanf(buf, "%d\n", &flag) != 1)
		return -EINVAL;
	if (flag) {
		rc = ap_poll_thread_start();
		if (rc)
			return rc;
	}
	else
		ap_poll_thread_stop();
	return count;
}