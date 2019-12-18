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
struct sysctl_req {int /*<<< orphan*/  newptr; } ;

/* Variables and functions */
 int SYSCTL_IN (struct sysctl_req*,void*,size_t) ; 
 int SYSCTL_OUT (struct sysctl_req*,void*,size_t) ; 

int sysctl_io_opaque(struct sysctl_req *req,void *pValue, size_t valueSize, int *changed)
{
	int error;

	if (changed) *changed = 0;

	/* Copy blob out */
	error = SYSCTL_OUT(req, pValue, valueSize);

	/* error or nothing to set */
	if (error || !req->newptr)
		return(error);

	error = SYSCTL_IN(req, pValue, valueSize);

	if (!error && changed)
		*changed = 1;
	return(error);
}