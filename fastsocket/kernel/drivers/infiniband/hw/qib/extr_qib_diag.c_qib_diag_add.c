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
struct qib_devdata {int unit; int /*<<< orphan*/  diag_device; int /*<<< orphan*/  diag_cdev; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int QIB_DIAGPKT_MINOR ; 
 int QIB_DIAG_MINOR_BASE ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diag_file_ops ; 
 int /*<<< orphan*/  diagpkt_cdev ; 
 int /*<<< orphan*/  diagpkt_count ; 
 int /*<<< orphan*/  diagpkt_device ; 
 int /*<<< orphan*/  diagpkt_file_ops ; 
 int qib_cdev_init (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int qib_diag_add(struct qib_devdata *dd)
{
	char name[16];
	int ret = 0;

	if (atomic_inc_return(&diagpkt_count) == 1) {
		ret = qib_cdev_init(QIB_DIAGPKT_MINOR, "ipath_diagpkt",
				    &diagpkt_file_ops, &diagpkt_cdev,
				    &diagpkt_device);
		if (ret)
			goto done;
	}

	snprintf(name, sizeof(name), "ipath_diag%d", dd->unit);
	ret = qib_cdev_init(QIB_DIAG_MINOR_BASE + dd->unit, name,
			    &diag_file_ops, &dd->diag_cdev,
			    &dd->diag_device);
done:
	return ret;
}