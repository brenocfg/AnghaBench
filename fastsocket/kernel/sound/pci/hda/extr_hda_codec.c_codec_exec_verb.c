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
struct hda_codec {int /*<<< orphan*/  addr; struct hda_bus* bus; } ;
struct TYPE_2__ {int (* command ) (struct hda_bus*,unsigned int) ;unsigned int (* get_response ) (struct hda_bus*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* bus_reset ) (struct hda_bus*) ;} ;
struct hda_bus {int no_response_fallback; scalar_t__ response_reset; TYPE_1__ ops; scalar_t__ rirb_error; int /*<<< orphan*/  cmd_mutex; } ;

/* Variables and functions */
 int EAGAIN ; 
 int HDA_RW_NO_RESPONSE_FALLBACK ; 
 scalar_t__ codec_in_pm (struct hda_codec*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_power_down (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_power_up (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 
 int stub1 (struct hda_bus*,unsigned int) ; 
 unsigned int stub2 (struct hda_bus*,int /*<<< orphan*/ ) ; 
 unsigned int stub3 (struct hda_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct hda_bus*) ; 
 int /*<<< orphan*/  trace_hda_bus_reset (struct hda_bus*) ; 
 int /*<<< orphan*/  trace_hda_get_response (struct hda_codec*,unsigned int) ; 
 int /*<<< orphan*/  trace_hda_send_cmd (struct hda_codec*,unsigned int) ; 

__attribute__((used)) static int codec_exec_verb(struct hda_codec *codec, unsigned int cmd,
			   int flags, unsigned int *res)
{
	struct hda_bus *bus = codec->bus;
	int err;

	if (cmd == ~0)
		return -1;

	if (res)
		*res = -1;
 again:
	snd_hda_power_up(codec);
	mutex_lock(&bus->cmd_mutex);
	if (flags & HDA_RW_NO_RESPONSE_FALLBACK)
		bus->no_response_fallback = 1;
	for (;;) {
		trace_hda_send_cmd(codec, cmd);
		err = bus->ops.command(bus, cmd);
		if (err != -EAGAIN)
			break;
		/* process pending verbs */
		bus->ops.get_response(bus, codec->addr);
	}
	if (!err && res) {
		*res = bus->ops.get_response(bus, codec->addr);
		trace_hda_get_response(codec, *res);
	}
	bus->no_response_fallback = 0;
	mutex_unlock(&bus->cmd_mutex);
	snd_hda_power_down(codec);
	if (!codec_in_pm(codec) && res && *res == -1 && bus->rirb_error) {
		if (bus->response_reset) {
			snd_printd("hda_codec: resetting BUS due to "
				   "fatal communication error\n");
			trace_hda_bus_reset(bus);
			bus->ops.bus_reset(bus);
		}
		goto again;
	}
	/* clear reset-flag when the communication gets recovered */
	if (!err || codec_in_pm(codec))
		bus->response_reset = 0;
	return err;
}