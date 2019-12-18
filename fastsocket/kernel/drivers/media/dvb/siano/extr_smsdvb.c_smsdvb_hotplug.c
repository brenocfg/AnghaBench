#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  capabilities; } ;
struct TYPE_13__ {int filternum; int feednum; TYPE_1__ dmx; int /*<<< orphan*/  stop_feed; int /*<<< orphan*/  start_feed; } ;
struct TYPE_12__ {int filternum; scalar_t__ capabilities; TYPE_1__* demux; } ;
struct TYPE_11__ {int /*<<< orphan*/  ops; } ;
struct smsdvb_client_t {int event_fe_state; int event_unc_state; int /*<<< orphan*/  adapter; TYPE_7__ demux; TYPE_5__ dmxdev; TYPE_3__ frontend; int /*<<< orphan*/  entry; int /*<<< orphan*/  tune_done; struct smscore_device_t* coredev; int /*<<< orphan*/  smsclient; } ;
struct smscore_device_t {int dummy; } ;
struct smsclient_params_t {int initial_id; struct smsdvb_client_t* context; int /*<<< orphan*/  onremove_handler; int /*<<< orphan*/  onresponse_handler; int /*<<< orphan*/  data_type; } ;
struct dvb_frontend_ops {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_TS_FILTERING ; 
 int /*<<< orphan*/  DVB3_EVENT_HOTPLUG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSG_SMS_DVBT_BDA_DATA ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adapter_nr ; 
 int dvb_dmx_init (TYPE_7__*) ; 
 int /*<<< orphan*/  dvb_dmx_release (TYPE_7__*) ; 
 int dvb_dmxdev_init (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (TYPE_5__*) ; 
 int dvb_register_adapter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ) ; 
 int dvb_register_frontend (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (TYPE_3__*) ; 
 int /*<<< orphan*/  g_smsdvb_clients ; 
 int /*<<< orphan*/  g_smsdvb_clientslock ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct smsdvb_client_t*) ; 
 int /*<<< orphan*/  kmutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmutex_unlock (int /*<<< orphan*/ *) ; 
 struct smsdvb_client_t* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sms_board_dvb3_event (struct smsdvb_client_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_board_setup (struct smscore_device_t*) ; 
 int /*<<< orphan*/  sms_err (char*,...) ; 
 TYPE_2__* sms_get_board (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_info (char*) ; 
 int /*<<< orphan*/  smscore_get_board_id (struct smscore_device_t*) ; 
 int smscore_register_client (struct smscore_device_t*,struct smsclient_params_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smsdvb_fe_ops ; 
 int /*<<< orphan*/  smsdvb_onremove ; 
 int /*<<< orphan*/  smsdvb_onresponse ; 
 int /*<<< orphan*/  smsdvb_start_feed ; 
 int /*<<< orphan*/  smsdvb_stop_feed ; 

__attribute__((used)) static int smsdvb_hotplug(struct smscore_device_t *coredev,
			  struct device *device, int arrival)
{
	struct smsclient_params_t params;
	struct smsdvb_client_t *client;
	int rc;

	/* device removal handled by onremove callback */
	if (!arrival)
		return 0;
	client = kzalloc(sizeof(struct smsdvb_client_t), GFP_KERNEL);
	if (!client) {
		sms_err("kmalloc() failed");
		return -ENOMEM;
	}

	/* register dvb adapter */
	rc = dvb_register_adapter(&client->adapter,
				  sms_get_board(
					smscore_get_board_id(coredev))->name,
				  THIS_MODULE, device, adapter_nr);
	if (rc < 0) {
		sms_err("dvb_register_adapter() failed %d", rc);
		goto adapter_error;
	}

	/* init dvb demux */
	client->demux.dmx.capabilities = DMX_TS_FILTERING;
	client->demux.filternum = 32; /* todo: nova ??? */
	client->demux.feednum = 32;
	client->demux.start_feed = smsdvb_start_feed;
	client->demux.stop_feed = smsdvb_stop_feed;

	rc = dvb_dmx_init(&client->demux);
	if (rc < 0) {
		sms_err("dvb_dmx_init failed %d", rc);
		goto dvbdmx_error;
	}

	/* init dmxdev */
	client->dmxdev.filternum = 32;
	client->dmxdev.demux = &client->demux.dmx;
	client->dmxdev.capabilities = 0;

	rc = dvb_dmxdev_init(&client->dmxdev, &client->adapter);
	if (rc < 0) {
		sms_err("dvb_dmxdev_init failed %d", rc);
		goto dmxdev_error;
	}

	/* init and register frontend */
	memcpy(&client->frontend.ops, &smsdvb_fe_ops,
	       sizeof(struct dvb_frontend_ops));

	rc = dvb_register_frontend(&client->adapter, &client->frontend);
	if (rc < 0) {
		sms_err("frontend registration failed %d", rc);
		goto frontend_error;
	}

	params.initial_id = 1;
	params.data_type = MSG_SMS_DVBT_BDA_DATA;
	params.onresponse_handler = smsdvb_onresponse;
	params.onremove_handler = smsdvb_onremove;
	params.context = client;

	rc = smscore_register_client(coredev, &params, &client->smsclient);
	if (rc < 0) {
		sms_err("smscore_register_client() failed %d", rc);
		goto client_error;
	}

	client->coredev = coredev;

	init_completion(&client->tune_done);

	kmutex_lock(&g_smsdvb_clientslock);

	list_add(&client->entry, &g_smsdvb_clients);

	kmutex_unlock(&g_smsdvb_clientslock);

	client->event_fe_state = -1;
	client->event_unc_state = -1;
	sms_board_dvb3_event(client, DVB3_EVENT_HOTPLUG);

	sms_info("success");
	sms_board_setup(coredev);

	return 0;

client_error:
	dvb_unregister_frontend(&client->frontend);

frontend_error:
	dvb_dmxdev_release(&client->dmxdev);

dmxdev_error:
	dvb_dmx_release(&client->demux);

dvbdmx_error:
	dvb_unregister_adapter(&client->adapter);

adapter_error:
	kfree(client);
	return rc;
}