#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* ipc_port_t ;
typedef  TYPE_5__* ipc_mqueue_t ;
typedef  TYPE_6__* ipc_kmsg_t ;
typedef  TYPE_7__* flipc_port_t ;
struct TYPE_19__ {int /*<<< orphan*/  name; } ;
struct TYPE_25__ {scalar_t__ state; int /*<<< orphan*/  lport; TYPE_1__ obj; } ;
struct TYPE_24__ {int /*<<< orphan*/  ikm_node; } ;
struct TYPE_20__ {int msgcount; TYPE_7__* fport; } ;
struct TYPE_21__ {TYPE_2__ port; } ;
struct TYPE_23__ {TYPE_3__ data; int /*<<< orphan*/  imq_seqno; int /*<<< orphan*/  imq_messages; } ;
struct TYPE_22__ {TYPE_5__ ip_messages; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_7__* FPORT_NULL ; 
 scalar_t__ FPORT_STATE_PRINCIPAL ; 
 int FPORT_VALID (TYPE_7__*) ; 
 TYPE_6__* IKM_NULL ; 
 int /*<<< orphan*/  IP_NULL ; 
 int IP_VALID (TYPE_4__*) ; 
 int MNL_NAME_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  flipc_msg_ack (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flipc_port_zone ; 
 TYPE_6__* ipc_kmsg_queue_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_kmsg_rmqueue (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  ipc_mqueue_release_msgcount (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mnl_obj_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_7__*) ; 

__attribute__((used)) static void
flipc_port_destroy(ipc_port_t lport)
{
    /* Ensure parameter is valid, and linked to an fport with a valid name */
    assert(IP_VALID(lport));
    ipc_mqueue_t port_mq = &lport->ip_messages;
    flipc_port_t fport = port_mq->data.port.fport;
    assert(FPORT_VALID(fport));
    assert(MNL_NAME_VALID(fport->obj.name));

    /* Dispose of any undelivered messages */
    int m = port_mq->data.port.msgcount;
    if (m > 0) {
        ipc_kmsg_t kmsg;
#if DEBUG
        printf("flipc: destroying %p with %d undelivered msgs\n", lport, m);
#endif

        /* Logic was lifted from ipc_mqueue_select_on_thread() */
        while (m--) {
            kmsg = ipc_kmsg_queue_first(&port_mq->imq_messages);
            assert(kmsg != IKM_NULL);
            ipc_kmsg_rmqueue(&port_mq->imq_messages, kmsg);
            if (fport->state == FPORT_STATE_PRINCIPAL)
                flipc_msg_ack(kmsg->ikm_node, port_mq, FALSE);
            ipc_mqueue_release_msgcount(port_mq, NULL);
            port_mq->imq_seqno++;
        }
    }

    /* Remove from name hash table, unlink co-structures, and free fport */
    mnl_obj_remove(fport->obj.name);
    lport->ip_messages.data.port.fport = FPORT_NULL;
    fport->lport = IP_NULL;
    zfree(flipc_port_zone, fport);
}