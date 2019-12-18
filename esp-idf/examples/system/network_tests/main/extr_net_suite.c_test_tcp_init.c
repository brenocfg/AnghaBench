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
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  IP_ADDR_ANY ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tcp_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_bind (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * tcp_listen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tcp_new () ; 
 int /*<<< orphan*/  test_accept ; 
 int /*<<< orphan*/ * test_pcb ; 

void test_tcp_init(void)
{
    test_pcb = tcp_new();
    if (test_pcb != NULL) {
        err_t err;
        /* Binding this test_pcb to 4242 to accept connections on this port
         * - this has to be configured as DUT endpoint
         * - all network traffic from and to network stack is tracked in nettestif
         */
        err = tcp_bind(test_pcb, IP_ADDR_ANY, 4242);
        if (err == ERR_OK) {
            test_pcb = tcp_listen(test_pcb);
            tcp_accept(test_pcb, test_accept);
        } else  {
            printf("cannot bind test_pcb\n");
            abort();
        }
    } else  {
        printf("cannot create test_pcb\n");
        abort();
    }
}