#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned short req_reply_port; } ;
typedef  TYPE_1__ kdp_reattach_req_t ;
struct TYPE_7__ {TYPE_1__ reattach_req; } ;
typedef  TYPE_2__ kdp_pkt_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  is_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_5__ kdp ; 
 int /*<<< orphan*/  kdp_disconnect (TYPE_2__*,int*,unsigned short*) ; 
 int reattach_wait ; 

__attribute__((used)) static boolean_t
kdp_reattach(
    kdp_pkt_t		*pkt,
    int			*len,
    unsigned short	*reply_port
)
{
    kdp_reattach_req_t            *rq = &pkt->reattach_req;

    kdp.is_conn = TRUE;
    kdp_disconnect(pkt, len, reply_port);
    *reply_port = rq->req_reply_port;
    reattach_wait = 1;
    return (TRUE);
}