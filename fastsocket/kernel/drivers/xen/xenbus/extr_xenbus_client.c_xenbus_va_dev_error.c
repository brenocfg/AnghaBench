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
typedef  int /*<<< orphan*/  va_list ;
struct xenbus_device {int /*<<< orphan*/  nodename; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PRINTF_BUFFER_SIZE ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,...) ; 
 char* error_path (struct xenbus_device*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int sprintf (char*,char*,int) ; 
 int vsnprintf (char*,unsigned int,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ xenbus_write (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static void xenbus_va_dev_error(struct xenbus_device *dev, int err,
				const char *fmt, va_list ap)
{
	int ret;
	unsigned int len;
	char *printf_buffer = NULL;
	char *path_buffer = NULL;

#define PRINTF_BUFFER_SIZE 4096
	printf_buffer = kmalloc(PRINTF_BUFFER_SIZE, GFP_KERNEL);
	if (printf_buffer == NULL)
		goto fail;

	len = sprintf(printf_buffer, "%i ", -err);
	ret = vsnprintf(printf_buffer+len, PRINTF_BUFFER_SIZE-len, fmt, ap);

	BUG_ON(len + ret > PRINTF_BUFFER_SIZE-1);

	dev_err(&dev->dev, "%s\n", printf_buffer);

	path_buffer = error_path(dev);

	if (path_buffer == NULL) {
		dev_err(&dev->dev, "failed to write error node for %s (%s)\n",
		       dev->nodename, printf_buffer);
		goto fail;
	}

	if (xenbus_write(XBT_NIL, path_buffer, "error", printf_buffer) != 0) {
		dev_err(&dev->dev, "failed to write error node for %s (%s)\n",
		       dev->nodename, printf_buffer);
		goto fail;
	}

fail:
	kfree(printf_buffer);
	kfree(path_buffer);
}