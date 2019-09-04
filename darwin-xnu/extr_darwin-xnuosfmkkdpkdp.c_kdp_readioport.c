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
typedef  scalar_t__ uint16_t ;
struct TYPE_9__ {scalar_t__ nbytes; int /*<<< orphan*/  lcpu; } ;
typedef  TYPE_2__ kdp_readioport_req_t ;
struct TYPE_8__ {int is_reply; int len; } ;
struct TYPE_10__ {scalar_t__ error; TYPE_1__ hdr; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ kdp_readioport_reply_t ;
struct TYPE_11__ {TYPE_3__ readioport_reply; TYPE_2__ readioport_req; } ;
typedef  TYPE_4__ kdp_pkt_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_12__ {unsigned short reply_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KDPERR_BAD_NBYTES ; 
 scalar_t__ KDPERR_NO_ERROR ; 
 scalar_t__ MAX_KDP_DATA_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  addr ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 TYPE_7__ kdp ; 
 scalar_t__ kdp_machine_ioport_read (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
kdp_readioport(
    kdp_pkt_t		*pkt,
    int			*len,
    unsigned short	*reply_port
	       )
{
	kdp_readioport_req_t   *rq = &pkt->readioport_req;
	kdp_readioport_reply_t *rp = &pkt->readioport_reply;
	size_t plen = *len;

	if (plen < sizeof (*rq))
		return (FALSE);
	
	rp->hdr.is_reply = 1;
	rp->hdr.len = sizeof (*rp);
	
	if (rq->nbytes > MAX_KDP_DATA_SIZE)
		rp->error = KDPERR_BAD_NBYTES;
	else {
#if KDP_TEST_HARNESS
                uint16_t addr = rq->address;
#endif
		uint16_t size = rq->nbytes;
		dprintf(("kdp_readioport addr %x size %d\n", addr, size));

		rp->error = kdp_machine_ioport_read(rq, rp->data, rq->lcpu);
		if (rp->error == KDPERR_NO_ERROR)
			rp->hdr.len += size;
	}
	
	*reply_port = kdp.reply_port;
	*len = rp->hdr.len;
    
	return (TRUE);
}