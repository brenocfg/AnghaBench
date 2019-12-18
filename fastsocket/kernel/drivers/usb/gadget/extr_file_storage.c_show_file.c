#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lun {TYPE_1__* filp; } ;
struct fsg_dev {int /*<<< orphan*/  filesem; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 scalar_t__ PAGE_SIZE ; 
 size_t PTR_ERR (char*) ; 
 scalar_t__ backing_file_is_open (struct lun*) ; 
 char* d_path (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 struct fsg_dev* dev_get_drvdata (struct device*) ; 
 struct lun* dev_to_lun (struct device*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t show_file(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct lun	*curlun = dev_to_lun(dev);
	struct fsg_dev	*fsg = dev_get_drvdata(dev);
	char		*p;
	ssize_t		rc;

	down_read(&fsg->filesem);
	if (backing_file_is_open(curlun)) {	// Get the complete pathname
		p = d_path(&curlun->filp->f_path, buf, PAGE_SIZE - 1);
		if (IS_ERR(p))
			rc = PTR_ERR(p);
		else {
			rc = strlen(p);
			memmove(buf, p, rc);
			buf[rc] = '\n';		// Add a newline
			buf[++rc] = 0;
		}
	} else {				// No file, return 0 bytes
		*buf = 0;
		rc = 0;
	}
	up_read(&fsg->filesem);
	return rc;
}