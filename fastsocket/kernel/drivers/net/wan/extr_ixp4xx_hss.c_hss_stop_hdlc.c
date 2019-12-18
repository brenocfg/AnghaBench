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
struct port {int /*<<< orphan*/  id; } ;
struct msg {int /*<<< orphan*/  hss_port; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  PKT_PIPE_FLOW_DISABLE ; 
 int /*<<< orphan*/  hss_get_status (struct port*) ; 
 int /*<<< orphan*/  hss_npe_send (struct port*,struct msg*,char*) ; 
 int /*<<< orphan*/  memset (struct msg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hss_stop_hdlc(struct port *port)
{
	struct msg msg;

	memset(&msg, 0, sizeof(msg));
	msg.cmd = PKT_PIPE_FLOW_DISABLE;
	msg.hss_port = port->id;
	hss_npe_send(port, &msg, "HSS_DISABLE_PKT_PIPE");
	hss_get_status(port); /* make sure it's halted */
}