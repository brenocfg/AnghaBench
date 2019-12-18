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
typedef  int /*<<< orphan*/  value ;
struct sysctl_req {int /*<<< orphan*/  newptr; } ;

/* Variables and functions */
 int ktrace_get_owning_pid () ; 
 int ktrace_set_owning_pid (int) ; 
 int sysctl_io_number (struct sysctl_req*,int,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sysctl_bless(struct sysctl_req *req)
{
	int value = ktrace_get_owning_pid();
	int error = sysctl_io_number(req, value, sizeof(value), &value, NULL);

	if (error || !req->newptr) {
		return error;
	}

	return ktrace_set_owning_pid(value);
}