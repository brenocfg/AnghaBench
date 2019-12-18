#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int value; } ;
struct TYPE_9__ {TYPE_3__ param; int /*<<< orphan*/  queue; } ;
struct TYPE_10__ {TYPE_4__ queue; } ;
struct TYPE_7__ {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct TYPE_6__ {scalar_t__ port; int /*<<< orphan*/  client; } ;
struct snd_seq_event {int type; TYPE_5__ data; int /*<<< orphan*/  queue; TYPE_2__ dest; TYPE_1__ source; } ;
struct seq_oss_devinfo {int /*<<< orphan*/  cseq; int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_SEQ_CLIENT_SYSTEM ; 
 int /*<<< orphan*/  SNDRV_SEQ_PORT_SYSTEM_TIMER ; 
 int /*<<< orphan*/  memset (struct snd_seq_event*,int /*<<< orphan*/ ,int) ; 
 int snd_seq_kernel_client_dispatch (int /*<<< orphan*/ ,struct snd_seq_event*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
send_timer_event(struct seq_oss_devinfo *dp, int type, int value)
{
	struct snd_seq_event ev;

	memset(&ev, 0, sizeof(ev));
	ev.type = type;
	ev.source.client = dp->cseq;
	ev.source.port = 0;
	ev.dest.client = SNDRV_SEQ_CLIENT_SYSTEM;
	ev.dest.port = SNDRV_SEQ_PORT_SYSTEM_TIMER;
	ev.queue = dp->queue;
	ev.data.queue.queue = dp->queue;
	ev.data.queue.param.value = value;
	return snd_seq_kernel_client_dispatch(dp->cseq, &ev, 1, 0);
}