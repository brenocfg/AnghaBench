#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int len; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  flavor; int /*<<< orphan*/  cpu; TYPE_1__ hdr; } ;
typedef  TYPE_3__ kdp_writeregs_req_t ;
struct TYPE_9__ {int is_reply; int len; } ;
struct TYPE_11__ {TYPE_2__ hdr; int /*<<< orphan*/  error; } ;
typedef  TYPE_4__ kdp_writeregs_reply_t ;
struct TYPE_12__ {TYPE_4__ writeregs_reply; TYPE_3__ writeregs_req; } ;
typedef  TYPE_5__ kdp_pkt_t ;
typedef  int /*<<< orphan*/  kdp_hdr_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_13__ {unsigned short reply_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_7__ kdp ; 
 int /*<<< orphan*/  kdp_machine_write_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static boolean_t
kdp_writeregs(
    kdp_pkt_t		*pkt,
    int			*len,
    unsigned short	*reply_port
)
{
    kdp_writeregs_req_t	*rq = &pkt->writeregs_req;
    size_t		plen = *len;
    int			size;
    kdp_writeregs_reply_t *rp = &pkt->writeregs_reply;

    if (plen < sizeof (*rq))
	return (FALSE);
    
    size = rq->hdr.len - (unsigned)sizeof(kdp_hdr_t) - (unsigned)sizeof(unsigned int);
    rp->error = kdp_machine_write_regs(rq->cpu, rq->flavor, rq->data, &size);

    rp->hdr.is_reply = 1;
    rp->hdr.len = sizeof (*rp);
    
    *reply_port = kdp.reply_port;
    *len = rp->hdr.len;
    
    return (TRUE);
}