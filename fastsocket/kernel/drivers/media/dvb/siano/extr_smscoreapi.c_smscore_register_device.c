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
typedef  int /*<<< orphan*/  u8 ;
struct smsdevice_params_t {int buffer_size; int num_buffers; int /*<<< orphan*/  device_type; int /*<<< orphan*/  devpath; int /*<<< orphan*/  flags; int /*<<< orphan*/  postload_handler; int /*<<< orphan*/  preload_handler; int /*<<< orphan*/  sendrequest_handler; int /*<<< orphan*/  detectmode_handler; int /*<<< orphan*/  setmode_handler; int /*<<< orphan*/  device; int /*<<< orphan*/  context; } ;
struct smscore_device_t {int common_buffer_size; scalar_t__ num_buffers; int /*<<< orphan*/  entry; int /*<<< orphan*/  devpath; int /*<<< orphan*/  device_flags; int /*<<< orphan*/  postload_handler; int /*<<< orphan*/  preload_handler; int /*<<< orphan*/  sendrequest_handler; int /*<<< orphan*/  detectmode_handler; int /*<<< orphan*/  setmode_handler; int /*<<< orphan*/  device; int /*<<< orphan*/  context; int /*<<< orphan*/  mode; int /*<<< orphan*/  common_buffer_phys; int /*<<< orphan*/ * common_buffer; int /*<<< orphan*/  buffer_mng_waitq; int /*<<< orphan*/  ir_init_done; int /*<<< orphan*/  gpio_get_level_done; int /*<<< orphan*/  gpio_set_level_done; int /*<<< orphan*/  gpio_configuration_done; int /*<<< orphan*/  resume_done; int /*<<< orphan*/  reload_start_done; int /*<<< orphan*/  init_device_done; int /*<<< orphan*/  trigger_done; int /*<<< orphan*/  data_download_done; int /*<<< orphan*/  version_ex_done; int /*<<< orphan*/  bufferslock; int /*<<< orphan*/  clientslock; int /*<<< orphan*/  buffers; int /*<<< orphan*/  clients; } ;
struct smscore_buffer_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_MODE_NONE ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  g_smscore_devices ; 
 int /*<<< orphan*/  g_smscore_deviceslock ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmutex_unlock (int /*<<< orphan*/ *) ; 
 struct smscore_device_t* kzalloc (int,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sms_info (char*,...) ; 
 struct smscore_buffer_t* smscore_createbuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smscore_putbuffer (struct smscore_device_t*,struct smscore_buffer_t*) ; 
 int /*<<< orphan*/  smscore_registry_settype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smscore_unregister_device (struct smscore_device_t*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int smscore_register_device(struct smsdevice_params_t *params,
			    struct smscore_device_t **coredev)
{
	struct smscore_device_t *dev;
	u8 *buffer;

	dev = kzalloc(sizeof(struct smscore_device_t), GFP_KERNEL);
	if (!dev) {
		sms_info("kzalloc(...) failed");
		return -ENOMEM;
	}

	/* init list entry so it could be safe in smscore_unregister_device */
	INIT_LIST_HEAD(&dev->entry);

	/* init queues */
	INIT_LIST_HEAD(&dev->clients);
	INIT_LIST_HEAD(&dev->buffers);

	/* init locks */
	spin_lock_init(&dev->clientslock);
	spin_lock_init(&dev->bufferslock);

	/* init completion events */
	init_completion(&dev->version_ex_done);
	init_completion(&dev->data_download_done);
	init_completion(&dev->trigger_done);
	init_completion(&dev->init_device_done);
	init_completion(&dev->reload_start_done);
	init_completion(&dev->resume_done);
	init_completion(&dev->gpio_configuration_done);
	init_completion(&dev->gpio_set_level_done);
	init_completion(&dev->gpio_get_level_done);
	init_completion(&dev->ir_init_done);

	/* Buffer management */
	init_waitqueue_head(&dev->buffer_mng_waitq);

	/* alloc common buffer */
	dev->common_buffer_size = params->buffer_size * params->num_buffers;
	dev->common_buffer = dma_alloc_coherent(NULL, dev->common_buffer_size,
						&dev->common_buffer_phys,
						GFP_KERNEL | GFP_DMA);
	if (!dev->common_buffer) {
		smscore_unregister_device(dev);
		return -ENOMEM;
	}

	/* prepare dma buffers */
	for (buffer = dev->common_buffer;
	     dev->num_buffers < params->num_buffers;
	     dev->num_buffers++, buffer += params->buffer_size) {
		struct smscore_buffer_t *cb =
			smscore_createbuffer(buffer, dev->common_buffer,
					     dev->common_buffer_phys);
		if (!cb) {
			smscore_unregister_device(dev);
			return -ENOMEM;
		}

		smscore_putbuffer(dev, cb);
	}

	sms_info("allocated %d buffers", dev->num_buffers);

	dev->mode = DEVICE_MODE_NONE;
	dev->context = params->context;
	dev->device = params->device;
	dev->setmode_handler = params->setmode_handler;
	dev->detectmode_handler = params->detectmode_handler;
	dev->sendrequest_handler = params->sendrequest_handler;
	dev->preload_handler = params->preload_handler;
	dev->postload_handler = params->postload_handler;

	dev->device_flags = params->flags;
	strcpy(dev->devpath, params->devpath);

	smscore_registry_settype(dev->devpath, params->device_type);

	/* add device to devices list */
	kmutex_lock(&g_smscore_deviceslock);
	list_add(&dev->entry, &g_smscore_devices);
	kmutex_unlock(&g_smscore_deviceslock);

	*coredev = dev;

	sms_info("device %p created", dev);

	return 0;
}