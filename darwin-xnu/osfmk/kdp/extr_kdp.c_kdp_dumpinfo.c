#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int is_reply; int len; } ;
struct TYPE_11__ {TYPE_1__ hdr; } ;
struct TYPE_10__ {int type; int /*<<< orphan*/  port; int /*<<< orphan*/  routerip; int /*<<< orphan*/  destip; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {TYPE_4__ dumpinfo_reply; TYPE_3__ dumpinfo_req; } ;
typedef  TYPE_2__ kdp_pkt_t ;
typedef  TYPE_3__ kdp_dumpinfo_req_t ;
typedef  TYPE_4__ kdp_dumpinfo_reply_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_12__ {unsigned short reply_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int KDP_DUMPINFO_GETINFO ; 
 int KDP_DUMPINFO_MASK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 TYPE_7__ kdp ; 
 int /*<<< orphan*/  kdp_get_dump_info (TYPE_4__*) ; 
 int /*<<< orphan*/  kdp_set_dump_info (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
kdp_dumpinfo(
	kdp_pkt_t	*pkt,
	int		*len,
	unsigned short	*reply_port
	       )
{
	kdp_dumpinfo_req_t   *rq = &pkt->dumpinfo_req;
	kdp_dumpinfo_reply_t *rp = &pkt->dumpinfo_reply;
	size_t	plen = *len;
	
	if (plen < sizeof (*rq))
		return (FALSE);
	
	dprintf(("kdp_dumpinfo file=%s destip=%s routerip=%s\n", rq->name, rq->destip, rq->routerip));
	rp->hdr.is_reply = 1;
	rp->hdr.len = sizeof (*rp);
	
        if ((rq->type & KDP_DUMPINFO_MASK) != KDP_DUMPINFO_GETINFO) {
            kdp_set_dump_info(rq->type, rq->name, rq->destip, rq->routerip, 
                                rq->port);
        }

        /* gather some stats for reply */
        kdp_get_dump_info(rp);

	*reply_port = kdp.reply_port;
	*len = rp->hdr.len;
    
	return (TRUE);
}