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
struct tracing_data {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct tracing_data* tracing_data_get (struct list_head*,int,int) ; 
 int /*<<< orphan*/  tracing_data_put (struct tracing_data*) ; 

int read_tracing_data(int fd, struct list_head *pattrs)
{
	struct tracing_data *tdata;

	/*
	 * We work over the real file, so we can write data
	 * directly, no temp file is needed.
	 */
	tdata = tracing_data_get(pattrs, fd, false);
	if (!tdata)
		return -ENOMEM;

	tracing_data_put(tdata);
	return 0;
}