#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ req_cpu; size_t func_id; } ;
typedef  TYPE_1__ pal_func_cpu_u_t ;
typedef  int off_t ;
struct TYPE_5__ {int (* proc_read ) (char*) ;} ;

/* Variables and functions */
 scalar_t__ get_cpu () ; 
 TYPE_3__* palinfo_entries ; 
 int palinfo_handle_smp (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int stub1 (char*) ; 

__attribute__((used)) static int
palinfo_read_entry(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	int len=0;
	pal_func_cpu_u_t *f = (pal_func_cpu_u_t *)&data;

	/*
	 * in SMP mode, we may need to call another CPU to get correct
	 * information. PAL, by definition, is processor specific
	 */
	if (f->req_cpu == get_cpu())
		len = (*palinfo_entries[f->func_id].proc_read)(page);
	else
		len = palinfo_handle_smp(f, page);

	put_cpu();

	if (len <= off+count) *eof = 1;

	*start = page + off;
	len   -= off;

	if (len>count) len = count;
	if (len<0) len = 0;

	return len;
}