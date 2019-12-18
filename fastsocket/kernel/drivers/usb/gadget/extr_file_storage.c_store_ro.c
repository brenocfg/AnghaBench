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
struct lun {int ro; } ;
struct fsg_dev {int /*<<< orphan*/  filesem; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  LDBG (struct lun*,char*,...) ; 
 scalar_t__ backing_file_is_open (struct lun*) ; 
 struct fsg_dev* dev_get_drvdata (struct device*) ; 
 struct lun* dev_to_lun (struct device*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t store_ro(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	ssize_t		rc = count;
	struct lun	*curlun = dev_to_lun(dev);
	struct fsg_dev	*fsg = dev_get_drvdata(dev);
	int		i;

	if (sscanf(buf, "%d", &i) != 1)
		return -EINVAL;

	/* Allow the write-enable status to change only while the backing file
	 * is closed. */
	down_read(&fsg->filesem);
	if (backing_file_is_open(curlun)) {
		LDBG(curlun, "read-only status change prevented\n");
		rc = -EBUSY;
	} else {
		curlun->ro = !!i;
		LDBG(curlun, "read-only status set to %d\n", curlun->ro);
	}
	up_read(&fsg->filesem);
	return rc;
}