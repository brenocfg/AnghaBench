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
typedef  int /*<<< orphan*/  mach_vm_size_t ;
struct TYPE_9__ {unsigned int nbytes; int /*<<< orphan*/  lcpu; int /*<<< orphan*/  data; int /*<<< orphan*/  address; } ;
typedef  TYPE_2__ kdp_writephysmem64_req_t ;
struct TYPE_8__ {int is_reply; int len; } ;
struct TYPE_10__ {TYPE_1__ hdr; int /*<<< orphan*/  error; } ;
typedef  TYPE_3__ kdp_writephysmem64_reply_t ;
struct TYPE_11__ {TYPE_3__ writephysmem64_reply; TYPE_2__ writephysmem64_req; } ;
typedef  TYPE_4__ kdp_pkt_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_12__ {unsigned short reply_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KDPERR_ACCESS (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KDPERR_BAD_NBYTES ; 
 unsigned int MAX_KDP_DATA_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 TYPE_7__ kdp ; 
 int /*<<< orphan*/  kdp_machine_phys_write (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
kdp_writephysmem64(
    kdp_pkt_t		*pkt,
    int			*len,
    unsigned short	*reply_port
)
{
    kdp_writephysmem64_req_t	*rq = &pkt->writephysmem64_req;
    size_t		plen = *len;
    kdp_writephysmem64_reply_t *rp = &pkt->writephysmem64_reply;
    mach_vm_size_t 		cnt;
    unsigned int		size;
	
    if (plen < sizeof (*rq))
	return (FALSE);
	
    size = rq->nbytes;
    if (size > MAX_KDP_DATA_SIZE)
	rp->error = KDPERR_BAD_NBYTES;
    else {
	dprintf(("kdp_writephysmem64 addr %llx size %d\n", rq->address, size));
	cnt = kdp_machine_phys_write(rq, rq->data, rq->lcpu);
	rp->error = KDPERR_ACCESS(size, cnt);
	dprintf(("  cnt %lld error %d\n", cnt, rp->error));
    }
	
    rp->hdr.is_reply = 1;
    rp->hdr.len = sizeof (*rp);
	
    *reply_port = kdp.reply_port;
    *len = rp->hdr.len;
    
    return (TRUE);
}