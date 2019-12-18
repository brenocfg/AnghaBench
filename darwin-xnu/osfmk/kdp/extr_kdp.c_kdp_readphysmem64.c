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
typedef  scalar_t__ mach_vm_size_t ;
struct TYPE_9__ {unsigned int nbytes; int /*<<< orphan*/  lcpu; int /*<<< orphan*/  address; } ;
typedef  TYPE_2__ kdp_readphysmem64_req_t ;
struct TYPE_8__ {int is_reply; int len; } ;
struct TYPE_10__ {TYPE_1__ hdr; int /*<<< orphan*/  error; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ kdp_readphysmem64_reply_t ;
struct TYPE_11__ {TYPE_3__ readphysmem64_reply; TYPE_2__ readphysmem64_req; } ;
typedef  TYPE_4__ kdp_pkt_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_12__ {unsigned short reply_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KDPERR_ACCESS (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  KDPERR_BAD_NBYTES ; 
 unsigned int MAX_KDP_DATA_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 TYPE_7__ kdp ; 
 scalar_t__ kdp_machine_phys_read (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
kdp_readphysmem64(
    kdp_pkt_t		*pkt,
    int			*len,
    unsigned short	*reply_port
)
{
    kdp_readphysmem64_req_t	*rq = &pkt->readphysmem64_req;
    size_t		plen = *len;
    kdp_readphysmem64_reply_t *rp = &pkt->readphysmem64_reply;
    mach_vm_size_t	cnt;
    unsigned int	size;

    if (plen < sizeof (*rq))
	return (FALSE);
	
    rp->hdr.is_reply = 1;
    rp->hdr.len = sizeof (*rp);
	
    size = rq->nbytes;
    if (size > MAX_KDP_DATA_SIZE)
	rp->error = KDPERR_BAD_NBYTES;
    else {
	dprintf(("kdp_readphysmem64 addr %llx size %d\n", rq->address, size));
	cnt = kdp_machine_phys_read(rq, rp->data, rq->lcpu);
	rp->error = KDPERR_ACCESS(size, cnt);
	dprintf(("  cnt %lld error %d\n", cnt, rp->error));
		
	rp->hdr.len += cnt;
    }
	
    *reply_port = kdp.reply_port;
    *len = rp->hdr.len;
    
    return (TRUE);
}