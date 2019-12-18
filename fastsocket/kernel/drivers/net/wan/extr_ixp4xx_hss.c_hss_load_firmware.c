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
struct port {int initialized; int /*<<< orphan*/  id; int /*<<< orphan*/  dev; int /*<<< orphan*/  npe; } ;
struct msg {int data32; int /*<<< orphan*/  cmd; int /*<<< orphan*/  data16a; int /*<<< orphan*/  data8a; int /*<<< orphan*/  hss_port; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  HDLC_MAX_MRU ; 
 int /*<<< orphan*/  NPE_PKT_MODE_HDLC ; 
 int /*<<< orphan*/  PKT_NUM_PIPES ; 
 int /*<<< orphan*/  PKT_NUM_PIPES_WRITE ; 
 int /*<<< orphan*/  PKT_PIPE_FIFO_SIZEW ; 
 int /*<<< orphan*/  PKT_PIPE_FIFO_SIZEW_WRITE ; 
 int /*<<< orphan*/  PKT_PIPE_IDLE_PATTERN_WRITE ; 
 int /*<<< orphan*/  PKT_PIPE_MODE_WRITE ; 
 int /*<<< orphan*/  PKT_PIPE_RX_SIZE_WRITE ; 
 int /*<<< orphan*/  hss_npe_send (struct port*,struct msg*,char*) ; 
 int /*<<< orphan*/  memset (struct msg*,int /*<<< orphan*/ ,int) ; 
 int npe_load_firmware (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npe_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npe_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hss_load_firmware(struct port *port)
{
	struct msg msg;
	int err;

	if (port->initialized)
		return 0;

	if (!npe_running(port->npe) &&
	    (err = npe_load_firmware(port->npe, npe_name(port->npe),
				     port->dev)))
		return err;

	/* HDLC mode configuration */
	memset(&msg, 0, sizeof(msg));
	msg.cmd = PKT_NUM_PIPES_WRITE;
	msg.hss_port = port->id;
	msg.data8a = PKT_NUM_PIPES;
	hss_npe_send(port, &msg, "HSS_SET_PKT_PIPES");

	msg.cmd = PKT_PIPE_FIFO_SIZEW_WRITE;
	msg.data8a = PKT_PIPE_FIFO_SIZEW;
	hss_npe_send(port, &msg, "HSS_SET_PKT_FIFO");

	msg.cmd = PKT_PIPE_MODE_WRITE;
	msg.data8a = NPE_PKT_MODE_HDLC;
	/* msg.data8b = inv_mask */
	/* msg.data8c = or_mask */
	hss_npe_send(port, &msg, "HSS_SET_PKT_MODE");

	msg.cmd = PKT_PIPE_RX_SIZE_WRITE;
	msg.data16a = HDLC_MAX_MRU; /* including CRC */
	hss_npe_send(port, &msg, "HSS_SET_PKT_RX_SIZE");

	msg.cmd = PKT_PIPE_IDLE_PATTERN_WRITE;
	msg.data32 = 0x7F7F7F7F; /* ??? FIXME */
	hss_npe_send(port, &msg, "HSS_SET_PKT_IDLE");

	port->initialized = 1;
	return 0;
}