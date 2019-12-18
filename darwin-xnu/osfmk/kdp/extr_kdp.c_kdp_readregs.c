#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  flavor; int /*<<< orphan*/  cpu; } ;
typedef  TYPE_2__ kdp_readregs_req_t ;
struct TYPE_7__ {int is_reply; int len; } ;
struct TYPE_9__ {TYPE_1__ hdr; int /*<<< orphan*/  data; int /*<<< orphan*/  error; } ;
typedef  TYPE_3__ kdp_readregs_reply_t ;
struct TYPE_10__ {TYPE_3__ readregs_reply; TYPE_2__ readregs_req; } ;
typedef  TYPE_4__ kdp_pkt_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_11__ {unsigned short reply_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_6__ kdp ; 
 int /*<<< orphan*/  kdp_machine_read_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static boolean_t
kdp_readregs(
    kdp_pkt_t		*pkt,
    int			*len,
    unsigned short	*reply_port
)
{
    kdp_readregs_req_t	*rq = &pkt->readregs_req;
    size_t		plen = *len;
    kdp_readregs_reply_t *rp = &pkt->readregs_reply;
    int			size;

    if (plen < sizeof (*rq))
	return (FALSE);

    rp->hdr.is_reply = 1;
    rp->hdr.len = sizeof (*rp);
    
    rp->error = kdp_machine_read_regs(rq->cpu, rq->flavor, rp->data, &size);
    rp->hdr.len += size;
    
    *reply_port = kdp.reply_port;
    *len = rp->hdr.len;
    
    return (TRUE);
}