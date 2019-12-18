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
struct device {int dummy; } ;
struct comedi_device_file_info {TYPE_1__* device; } ;
struct comedi_devconfig {char* board_name; int /*<<< orphan*/  options; } ;
typedef  int /*<<< orphan*/  it ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int COMEDI_NAMELEN ; 
 unsigned int COMEDI_NDEVCONFOPTS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int comedi_alloc_board_minor (struct device*) ; 
 int /*<<< orphan*/  comedi_autoconfig ; 
 int comedi_device_attach (TYPE_1__*,struct comedi_devconfig*) ; 
 int /*<<< orphan*/  comedi_free_board_minor (int) ; 
 struct comedi_device_file_info* comedi_get_device_file_info (int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,unsigned int*) ; 
 int /*<<< orphan*/  kfree (unsigned int*) ; 
 unsigned int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct comedi_devconfig*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

int comedi_auto_config(struct device *hardware_device, const char *board_name,
		       const int *options, unsigned num_options)
{
	struct comedi_devconfig it;
	int minor;
	struct comedi_device_file_info *dev_file_info;
	int retval;
	unsigned *private_data = NULL;

	if (!comedi_autoconfig) {
		dev_set_drvdata(hardware_device, NULL);
		return 0;
	}

	minor = comedi_alloc_board_minor(hardware_device);
	if (minor < 0)
		return minor;

	private_data = kmalloc(sizeof(unsigned), GFP_KERNEL);
	if (private_data == NULL) {
		retval = -ENOMEM;
		goto cleanup;
	}
	*private_data = minor;
	dev_set_drvdata(hardware_device, private_data);

	dev_file_info = comedi_get_device_file_info(minor);

	memset(&it, 0, sizeof(it));
	strncpy(it.board_name, board_name, COMEDI_NAMELEN);
	it.board_name[COMEDI_NAMELEN - 1] = '\0';
	BUG_ON(num_options > COMEDI_NDEVCONFOPTS);
	memcpy(it.options, options, num_options * sizeof(int));

	mutex_lock(&dev_file_info->device->mutex);
	retval = comedi_device_attach(dev_file_info->device, &it);
	mutex_unlock(&dev_file_info->device->mutex);

cleanup:
	if (retval < 0) {
		kfree(private_data);
		comedi_free_board_minor(minor);
	}
	return retval;
}