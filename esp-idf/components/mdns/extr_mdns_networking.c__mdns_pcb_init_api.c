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
struct tcpip_api_call_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  err; int /*<<< orphan*/  ip_protocol; int /*<<< orphan*/  tcpip_if; } ;
typedef  TYPE_1__ mdns_api_call_t ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  _udp_pcb_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static err_t _mdns_pcb_init_api(struct tcpip_api_call_data *api_call_msg)
{
    mdns_api_call_t * msg = (mdns_api_call_t *)api_call_msg;
    msg->err = _udp_pcb_init(msg->tcpip_if, msg->ip_protocol);
    return msg->err;
}