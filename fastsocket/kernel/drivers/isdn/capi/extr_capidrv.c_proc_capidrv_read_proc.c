#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int off_t ;
struct TYPE_3__ {int /*<<< orphan*/  nsentdatapkt; int /*<<< orphan*/  nsentctlpkt; int /*<<< orphan*/  nrecvdatapkt; int /*<<< orphan*/  nrecvctlpkt; } ;
struct TYPE_4__ {TYPE_1__ ap; } ;

/* Variables and functions */
 TYPE_2__ global ; 
 scalar_t__ sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_capidrv_read_proc(char *page, char **start, off_t off,
                                       int count, int *eof, void *data)
{
	int len = 0;

	len += sprintf(page+len, "%lu %lu %lu %lu\n",
			global.ap.nrecvctlpkt,
			global.ap.nrecvdatapkt,
			global.ap.nsentctlpkt,
			global.ap.nsentdatapkt);
	if (off+count >= len)
	   *eof = 1;
	if (len < off)
           return 0;
	*start = page + off;
	return ((count < len-off) ? count : len-off);
}