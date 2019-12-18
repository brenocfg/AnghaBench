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
struct qeth_channel {scalar_t__ io_buf_no; scalar_t__ buf_no; int /*<<< orphan*/ * iob; } ;

/* Variables and functions */
 int QETH_CMD_BUFFER_NO ; 
 int /*<<< orphan*/  qeth_release_buffer (struct qeth_channel*,int /*<<< orphan*/ *) ; 

void qeth_clear_cmd_buffers(struct qeth_channel *channel)
{
	int cnt;

	for (cnt = 0; cnt < QETH_CMD_BUFFER_NO; cnt++)
		qeth_release_buffer(channel, &channel->iob[cnt]);
	channel->buf_no = 0;
	channel->io_buf_no = 0;
}