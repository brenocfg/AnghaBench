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
struct lun {int /*<<< orphan*/  unit_attention_data; scalar_t__ prevent_medium_removal; } ;
struct fsg_dev {int /*<<< orphan*/  filesem; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  LDBG (struct lun*,char*) ; 
 int /*<<< orphan*/  SS_MEDIUM_NOT_PRESENT ; 
 int /*<<< orphan*/  SS_NOT_READY_TO_READY_TRANSITION ; 
 scalar_t__ backing_file_is_open (struct lun*) ; 
 int /*<<< orphan*/  close_backing_file (struct lun*) ; 
 struct fsg_dev* dev_get_drvdata (struct device*) ; 
 struct lun* dev_to_lun (struct device*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int open_backing_file (struct lun*,char const*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t store_file(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct lun	*curlun = dev_to_lun(dev);
	struct fsg_dev	*fsg = dev_get_drvdata(dev);
	int		rc = 0;

	if (curlun->prevent_medium_removal && backing_file_is_open(curlun)) {
		LDBG(curlun, "eject attempt prevented\n");
		return -EBUSY;				// "Door is locked"
	}

	/* Remove a trailing newline */
	if (count > 0 && buf[count-1] == '\n')
		((char *) buf)[count-1] = 0;		// Ugh!

	/* Eject current medium */
	down_write(&fsg->filesem);
	if (backing_file_is_open(curlun)) {
		close_backing_file(curlun);
		curlun->unit_attention_data = SS_MEDIUM_NOT_PRESENT;
	}

	/* Load new medium */
	if (count > 0 && buf[0]) {
		rc = open_backing_file(curlun, buf);
		if (rc == 0)
			curlun->unit_attention_data =
					SS_NOT_READY_TO_READY_TRANSITION;
	}
	up_write(&fsg->filesem);
	return (rc < 0 ? rc : count);
}