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
struct sysctl_req {int /*<<< orphan*/  newptr; scalar_t__ oldptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int sysctl_io_number (struct sysctl_req*,int,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kperf_sysctl_get_set_int(struct sysctl_req *req,
	int (*get)(void), int (*set)(int))
{
	assert(req != NULL);
	assert(get != NULL);
	assert(set != NULL);

	int value = 0;
	if (req->oldptr) {
		value = get();
	}

	int error = sysctl_io_number(req, value, sizeof(value), &value, NULL);

	if (error || !req->newptr) {
		return error;
	}

	return set(value);
}