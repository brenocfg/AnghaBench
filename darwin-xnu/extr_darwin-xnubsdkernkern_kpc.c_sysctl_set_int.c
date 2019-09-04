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
struct sysctl_req {int dummy; } ;

/* Variables and functions */
 int SYSCTL_IN (struct sysctl_req*,int*,int) ; 

__attribute__((used)) static int
sysctl_set_int( struct sysctl_req *req, int (*set_func)(int))
{
	int error = 0;
	int value = 0;
    
	error = SYSCTL_IN( req, &value, sizeof(value) );
	if( error )
		return error;
    
	error = set_func( value );

	return error;
}