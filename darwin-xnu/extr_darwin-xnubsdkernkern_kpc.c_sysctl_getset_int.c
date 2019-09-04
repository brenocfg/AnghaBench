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
typedef  int uint32_t ;
struct sysctl_req {int /*<<< orphan*/  newptr; } ;
struct sysctl_oid {int dummy; } ;

/* Variables and functions */
 int sysctl_handle_int (struct sysctl_oid*,int*,int /*<<< orphan*/ ,struct sysctl_req*) ; 

__attribute__((used)) static int
sysctl_getset_int( struct sysctl_oid *oidp, struct sysctl_req *req,
                   int (*get_func)(void), int (*set_func)(int) )
{
	int error = 0;
	uint32_t value = 0;
    
	/* get the old value and process it */
	value = get_func();

	/* copy out the old value, get the new value */
	error = sysctl_handle_int(oidp, &value, 0, req);
	if (error || !req->newptr)
		return (error);

	/* if that worked, and we're writing... */
	error = set_func( value );

	return error;
}