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
struct tcp_pcb {int dummy; } ;
typedef  void* err_t ;

/* Variables and functions */
 void* ERR_OK ; 
 int /*<<< orphan*/  LWIP_UNUSED_ARG (void*) ; 
 int /*<<< orphan*/  TCP_PRIO_MIN ; 
 int /*<<< orphan*/  tcp_arg (struct tcp_pcb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_err (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_poll (struct tcp_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_recv (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_setprio (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_error ; 
 int /*<<< orphan*/  test_poll ; 
 int /*<<< orphan*/  test_recv ; 

err_t test_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
    LWIP_UNUSED_ARG(arg);
    LWIP_UNUSED_ARG(err);

    tcp_setprio(newpcb, TCP_PRIO_MIN);
    tcp_arg(newpcb, NULL);
    tcp_recv(newpcb, test_recv);
    tcp_err(newpcb, test_error);
    tcp_poll(newpcb, test_poll, 0);

    return ERR_OK;
}