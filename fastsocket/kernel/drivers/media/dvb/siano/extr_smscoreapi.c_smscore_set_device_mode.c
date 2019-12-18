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
struct smscore_device_t {int device_flags; int mode; int modes_supported; int (* setmode_handler ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  context; int /*<<< orphan*/  (* detectmode_handler ) (int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  devpath; int /*<<< orphan*/  init_device_done; } ;
struct TYPE_2__ {int /*<<< orphan*/  msgLength; } ;
struct SmsMsgData_ST {int* msgData; TYPE_1__ xMsgHeader; } ;
typedef  enum sms_device_type_st { ____Placeholder_sms_device_type_st } sms_device_type_st ;

/* Variables and functions */
 int DEVICE_MODE_DVBT ; 
 int DEVICE_MODE_DVBT_BDA ; 
 int DEVICE_MODE_RAW_TUNER ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  MSG_SMS_INIT_DEVICE_REQ ; 
 scalar_t__ SMS_ALIGN_ADDRESS (void*) ; 
 int SMS_DEVICE_FAMILY2 ; 
 int SMS_DEVICE_NOT_READY ; 
 scalar_t__ SMS_DMA_ALIGNMENT ; 
 int /*<<< orphan*/  SMS_INIT_MSG (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (scalar_t__,int) ; 
 int /*<<< orphan*/  sms_debug (char*,int) ; 
 int /*<<< orphan*/  sms_err (char*,...) ; 
 char* sms_get_fw_name (struct smscore_device_t*,int,int) ; 
 int /*<<< orphan*/  sms_info (char*,int) ; 
 int /*<<< orphan*/  sms_log (char*,char*) ; 
 int /*<<< orphan*/  sms_warn (char*,int,char*) ; 
 int smscore_detect_mode (struct smscore_device_t*) ; 
 char*** smscore_fw_lkup ; 
 int smscore_load_firmware_from_file (struct smscore_device_t*,char*,int /*<<< orphan*/ *) ; 
 int smscore_registry_gettype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smscore_registry_setmode (int /*<<< orphan*/ ,int) ; 
 int smscore_sendrequest_and_wait (struct smscore_device_t*,struct SmsMsgData_ST*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*) ; 
 int stub2 (int /*<<< orphan*/ ,int) ; 

int smscore_set_device_mode(struct smscore_device_t *coredev, int mode)
{
	void *buffer;
	int rc = 0;
	enum sms_device_type_st type;

	sms_debug("set device mode to %d", mode);
	if (coredev->device_flags & SMS_DEVICE_FAMILY2) {
		if (mode < DEVICE_MODE_DVBT || mode >= DEVICE_MODE_RAW_TUNER) {
			sms_err("invalid mode specified %d", mode);
			return -EINVAL;
		}

		smscore_registry_setmode(coredev->devpath, mode);

		if (!(coredev->device_flags & SMS_DEVICE_NOT_READY)) {
			rc = smscore_detect_mode(coredev);
			if (rc < 0) {
				sms_err("mode detect failed %d", rc);
				return rc;
			}
		}

		if (coredev->mode == mode) {
			sms_info("device mode %d already set", mode);
			return 0;
		}

		if (!(coredev->modes_supported & (1 << mode))) {
			char *fw_filename;

			type = smscore_registry_gettype(coredev->devpath);
			fw_filename = sms_get_fw_name(coredev, mode, type);

			rc = smscore_load_firmware_from_file(coredev,
							     fw_filename, NULL);
			if (rc < 0) {
				sms_warn("error %d loading firmware: %s, "
					 "trying again with default firmware",
					 rc, fw_filename);

				/* try again with the default firmware */
				fw_filename = smscore_fw_lkup[mode][type];
				rc = smscore_load_firmware_from_file(coredev,
							     fw_filename, NULL);

				if (rc < 0) {
					sms_warn("error %d loading "
						 "firmware: %s", rc,
						 fw_filename);
					return rc;
				}
			}
			sms_log("firmware download success: %s", fw_filename);
		} else
			sms_info("mode %d supported by running "
				 "firmware", mode);

		buffer = kmalloc(sizeof(struct SmsMsgData_ST) +
				 SMS_DMA_ALIGNMENT, GFP_KERNEL | GFP_DMA);
		if (buffer) {
			struct SmsMsgData_ST *msg =
				(struct SmsMsgData_ST *)
					SMS_ALIGN_ADDRESS(buffer);

			SMS_INIT_MSG(&msg->xMsgHeader, MSG_SMS_INIT_DEVICE_REQ,
				     sizeof(struct SmsMsgData_ST));
			msg->msgData[0] = mode;

			rc = smscore_sendrequest_and_wait(
				coredev, msg, msg->xMsgHeader.msgLength,
				&coredev->init_device_done);

			kfree(buffer);
		} else {
			sms_err("Could not allocate buffer for "
				"init device message.");
			rc = -ENOMEM;
		}
	} else {
		if (mode < DEVICE_MODE_DVBT || mode > DEVICE_MODE_DVBT_BDA) {
			sms_err("invalid mode specified %d", mode);
			return -EINVAL;
		}

		smscore_registry_setmode(coredev->devpath, mode);

		if (coredev->detectmode_handler)
			coredev->detectmode_handler(coredev->context,
						    &coredev->mode);

		if (coredev->mode != mode && coredev->setmode_handler)
			rc = coredev->setmode_handler(coredev->context, mode);
	}

	if (rc >= 0) {
		coredev->mode = mode;
		coredev->device_flags &= ~SMS_DEVICE_NOT_READY;
	}

	if (rc < 0)
		sms_err("return error code %d.", rc);
	return rc;
}