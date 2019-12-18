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
struct mca_device {int /*<<< orphan*/  proc_dev; int /*<<< orphan*/  slot; scalar_t__ (* procfn ) (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int off_t ;

/* Variables and functions */
 int mca_default_procfn (char*,struct mca_device*) ; 
 scalar_t__ stub1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mca_read_proc(char *page, char **start, off_t off,
				 int count, int *eof, void *data)
{
	struct mca_device *mca_dev = (struct mca_device *)data;
	int len = 0;

	/* Get the standard info */

	len = mca_default_procfn(page, mca_dev);

	/* Do any device-specific processing, if there is any */

	if(mca_dev->procfn) {
		len += mca_dev->procfn(page+len, mca_dev->slot,
				       mca_dev->proc_dev);
	}
	if (len <= off+count) *eof = 1;
	*start = page + off;
	len -= off;
	if (len>count) len = count;
	if (len<0) len = 0;
	return len;
}