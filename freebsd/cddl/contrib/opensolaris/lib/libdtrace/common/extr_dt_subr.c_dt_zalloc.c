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
typedef  int /*<<< orphan*/  dtrace_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  bzero (void*,size_t) ; 
 int /*<<< orphan*/  dt_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* malloc (size_t) ; 

void *
dt_zalloc(dtrace_hdl_t *dtp, size_t size)
{
	void *data;

	if ((data = malloc(size)) == NULL)
		(void) dt_set_errno(dtp, EDT_NOMEM);
	else
		bzero(data, size);

	return (data);
}