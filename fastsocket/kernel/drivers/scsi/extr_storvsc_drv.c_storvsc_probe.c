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
struct vmscsi_win8_extension {int dummy; } ;
struct storvsc_device {int destroy; int open_sub_channel; int /*<<< orphan*/  target_id; int /*<<< orphan*/  path_id; int /*<<< orphan*/  port_number; struct Scsi_Host* host; struct hv_device* device; int /*<<< orphan*/  waiting_to_drain; } ;
struct hv_vmbus_device_id {scalar_t__ driver_data; } ;
struct hv_host_device {int /*<<< orphan*/  target; int /*<<< orphan*/  path; struct hv_device* dev; int /*<<< orphan*/  port; } ;
struct TYPE_2__ {int* b; } ;
struct hv_device {TYPE_1__ dev_instance; int /*<<< orphan*/  device; } ;
struct Scsi_Host {int /*<<< orphan*/  max_cmd_len; scalar_t__ max_channel; int /*<<< orphan*/  max_id; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IDE_GUID ; 
 int /*<<< orphan*/  POST_WIN7_STORVSC_SENSE_BUFFER_SIZE ; 
 int /*<<< orphan*/  PRE_WIN8_STORVSC_SENSE_BUFFER_SIZE ; 
 scalar_t__ STORVSC_MAX_CHANNELS ; 
 int /*<<< orphan*/  STORVSC_MAX_CMD_LEN ; 
 int /*<<< orphan*/  STORVSC_MAX_LUNS_PER_TARGET ; 
 int /*<<< orphan*/  STORVSC_MAX_TARGETS ; 
 scalar_t__ VERSION_WIN8 ; 
 int /*<<< orphan*/  VMSTOR_WIN7_MAJOR ; 
 int /*<<< orphan*/  VMSTOR_WIN7_MINOR ; 
 int /*<<< orphan*/  VMSTOR_WIN8_MAJOR ; 
 int /*<<< orphan*/  VMSTOR_WIN8_MINOR ; 
 int /*<<< orphan*/  hv_set_drvdata (struct hv_device*,struct storvsc_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct storvsc_device*) ; 
 struct storvsc_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hv_host_device*,int /*<<< orphan*/ ,int) ; 
 int scsi_add_device (struct Scsi_Host*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_driver ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sense_buffer_size ; 
 struct hv_host_device* shost_priv (struct Scsi_Host*) ; 
 int storvsc_connect_to_vsp (struct hv_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storvsc_dev_remove (struct hv_device*) ; 
 int /*<<< orphan*/  storvsc_ringbuffer_size ; 
 scalar_t__ vmbus_proto_version ; 
 int vmscsi_size_delta ; 
 int /*<<< orphan*/  vmstor_current_major ; 
 int /*<<< orphan*/  vmstor_current_minor ; 

__attribute__((used)) static int storvsc_probe(struct hv_device *device,
			const struct hv_vmbus_device_id *dev_id)
{
	int ret;
	struct Scsi_Host *host;
	struct hv_host_device *host_dev;
	bool dev_is_ide = ((dev_id->driver_data == IDE_GUID) ? true : false);
	int target = 0;
	struct storvsc_device *stor_device;

	/*
	 * Based on the windows host we are running on,
	 * set state to properly communicate with the host.
	 */

	if (vmbus_proto_version == VERSION_WIN8) {
		sense_buffer_size = POST_WIN7_STORVSC_SENSE_BUFFER_SIZE;
		vmscsi_size_delta = 0;
		vmstor_current_major = VMSTOR_WIN8_MAJOR;
		vmstor_current_minor = VMSTOR_WIN8_MINOR;
	} else {
		sense_buffer_size = PRE_WIN8_STORVSC_SENSE_BUFFER_SIZE;
		vmscsi_size_delta = sizeof(struct vmscsi_win8_extension);
		vmstor_current_major = VMSTOR_WIN7_MAJOR;
		vmstor_current_minor = VMSTOR_WIN7_MINOR;
	}


	host = scsi_host_alloc(&scsi_driver,
			       sizeof(struct hv_host_device));
	if (!host)
		return -ENOMEM;

	host_dev = shost_priv(host);
	memset(host_dev, 0, sizeof(struct hv_host_device));

	host_dev->port = host->host_no;
	host_dev->dev = device;


	stor_device = kzalloc(sizeof(struct storvsc_device), GFP_KERNEL);
	if (!stor_device) {
		ret = -ENOMEM;
		goto err_out0;
	}

	stor_device->destroy = false;
	stor_device->open_sub_channel = false;
	init_waitqueue_head(&stor_device->waiting_to_drain);
	stor_device->device = device;
	stor_device->host = host;
	hv_set_drvdata(device, stor_device);

	stor_device->port_number = host->host_no;
	ret = storvsc_connect_to_vsp(device, storvsc_ringbuffer_size);
	if (ret)
		goto err_out1;

	host_dev->path = stor_device->path_id;
	host_dev->target = stor_device->target_id;

	/* max # of devices per target */
	host->max_lun = STORVSC_MAX_LUNS_PER_TARGET;
	/* max # of targets per channel */
	host->max_id = STORVSC_MAX_TARGETS;
	/* max # of channels */
	host->max_channel = STORVSC_MAX_CHANNELS - 1;
	/* max cmd length */
	host->max_cmd_len = STORVSC_MAX_CMD_LEN;

	/* Register the HBA and start the scsi bus scan */
	ret = scsi_add_host(host, &device->device);
	if (ret != 0)
		goto err_out2;

	if (!dev_is_ide) {
		scsi_scan_host(host);
	} else {
		target = (device->dev_instance.b[5] << 8 |
			 device->dev_instance.b[4]);
		ret = scsi_add_device(host, 0, target, 0);
		if (ret) {
			scsi_remove_host(host);
			goto err_out2;
		}
	}
	return 0;

err_out2:
	/*
	 * Once we have connected with the host, we would need to
	 * to invoke storvsc_dev_remove() to rollback this state and
	 * this call also frees up the stor_device; hence the jump around
	 * err_out1 label.
	 */
	storvsc_dev_remove(device);
	goto err_out0;

err_out1:
	kfree(stor_device);

err_out0:
	scsi_host_put(host);
	return ret;
}