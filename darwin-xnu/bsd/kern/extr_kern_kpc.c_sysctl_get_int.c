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
typedef  int /*<<< orphan*/  uint32_t ;
struct sysctl_req {int dummy; } ;
struct sysctl_oid {int dummy; } ;

/* Variables and functions */
 int sysctl_handle_int (struct sysctl_oid*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sysctl_req*) ; 

__attribute__((used)) static int
sysctl_get_int( struct sysctl_oid *oidp, struct sysctl_req *req,
                uint32_t value )
{
	int error = 0;
    
	/* copy out the old value */
	error = sysctl_handle_int(oidp, &value, 0, req);
    
	return error;
}