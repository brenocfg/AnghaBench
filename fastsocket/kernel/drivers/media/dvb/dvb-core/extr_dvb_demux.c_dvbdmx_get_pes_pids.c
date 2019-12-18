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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_demux {int /*<<< orphan*/  pids; } ;
struct dmx_demux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dvbdmx_get_pes_pids(struct dmx_demux *demux, u16 * pids)
{
	struct dvb_demux *dvbdemux = (struct dvb_demux *)demux;

	memcpy(pids, dvbdemux->pids, 5 * sizeof(u16));
	return 0;
}