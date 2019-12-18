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
struct list_head {int dummy; } ;
struct dvb_demux {struct list_head frontend_list; } ;
struct dmx_frontend {int /*<<< orphan*/  connectivity_list; } ;
struct dmx_demux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static int dvbdmx_add_frontend(struct dmx_demux *demux,
			       struct dmx_frontend *frontend)
{
	struct dvb_demux *dvbdemux = (struct dvb_demux *)demux;
	struct list_head *head = &dvbdemux->frontend_list;

	list_add(&(frontend->connectivity_list), head);

	return 0;
}