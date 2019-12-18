#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dvb_demux_feed {int /*<<< orphan*/  pes_type; struct dvb_demux* demux; } ;
struct TYPE_6__ {TYPE_1__* frontend; } ;
struct dvb_demux {TYPE_2__ dmx; scalar_t__ priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  stream_source; } ;
struct TYPE_7__ {int /*<<< orphan*/  stream_source; } ;
struct av7110 {TYPE_4__ videostate; TYPE_3__ audiostate; scalar_t__ full_ts; } ;
struct TYPE_5__ {scalar_t__ source; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_SOURCE_MEMORY ; 
 scalar_t__ DMX_MEMORY_FE ; 
 int EINVAL ; 
 int /*<<< orphan*/  VIDEO_SOURCE_MEMORY ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 int write_ts_to_decoder (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

int av7110_write_to_decoder(struct dvb_demux_feed *feed, const u8 *buf, size_t len)
{
	struct dvb_demux *demux = feed->demux;
	struct av7110 *av7110 = (struct av7110 *) demux->priv;

	dprintk(2, "av7110:%p, \n", av7110);

	if (av7110->full_ts && demux->dmx.frontend->source != DMX_MEMORY_FE)
		return 0;

	switch (feed->pes_type) {
	case 0:
		if (av7110->audiostate.stream_source == AUDIO_SOURCE_MEMORY)
			return -EINVAL;
		break;
	case 1:
		if (av7110->videostate.stream_source == VIDEO_SOURCE_MEMORY)
			return -EINVAL;
		break;
	default:
		return -1;
	}

	return write_ts_to_decoder(av7110, feed->pes_type, buf, len);
}