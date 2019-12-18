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
struct TYPE_9__ {scalar_t__ nbytes; int /*<<< orphan*/  lcpu; int /*<<< orphan*/  data; int /*<<< orphan*/  address; } ;
typedef  TYPE_2__ kdp_writeioport_req_t ;
struct TYPE_8__ {int is_reply; int len; } ;
struct TYPE_10__ {TYPE_1__ hdr; int /*<<< orphan*/  error; } ;
typedef  TYPE_3__ kdp_writeioport_reply_t ;
struct TYPE_11__ {TYPE_3__ writeioport_reply; TYPE_2__ writeioport_req; } ;
typedef  TYPE_4__ kdp_pkt_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_12__ {unsigned short reply_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KDPERR_BAD_NBYTES ; 
 scalar_t__ MAX_KDP_DATA_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 TYPE_7__ kdp ; 
 int /*<<< orphan*/  kdp_machine_ioport_write (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
kdp_writeioport(
	kdp_pkt_t	*pkt,
	int		*len,
	unsigned short	*reply_port
                )
{
	kdp_writeioport_req_t   *rq = &pkt->writeioport_req;
	kdp_writeioport_reply_t *rp = &pkt->writeioport_reply;
	size_t	plen = *len;
	
	if (plen < sizeof (*rq))
		return (FALSE);
	
	if (rq->nbytes > MAX_KDP_DATA_SIZE)
		rp->error = KDPERR_BAD_NBYTES;
	else {
		dprintf(("kdp_writeioport addr %x size %d\n", rq->address, 
			rq->nbytes));
		
		rp->error = kdp_machine_ioport_write(rq, rq->data, rq->lcpu);
	}
	
	rp->hdr.is_reply = 1;
	rp->hdr.len = sizeof (*rp);
	
	*reply_port = kdp.reply_port;
	*len = rp->hdr.len;
    
	return (TRUE);
}