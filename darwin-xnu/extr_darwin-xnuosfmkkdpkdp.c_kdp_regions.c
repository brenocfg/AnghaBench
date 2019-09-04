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
typedef  int /*<<< orphan*/  kdp_regions_req_t ;
struct TYPE_7__ {int is_reply; int len; } ;
struct TYPE_8__ {int nregions; TYPE_1__ hdr; TYPE_3__* regions; } ;
typedef  TYPE_2__ kdp_regions_reply_t ;
struct TYPE_9__ {int nbytes; int /*<<< orphan*/  protection; scalar_t__ address; } ;
typedef  TYPE_3__ kdp_region_t ;
struct TYPE_10__ {TYPE_2__ regions_reply; int /*<<< orphan*/  regions_req; } ;
typedef  TYPE_4__ kdp_pkt_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_11__ {unsigned short reply_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 TYPE_6__ kdp ; 

__attribute__((used)) static boolean_t
kdp_regions(
    kdp_pkt_t		*pkt,
    int			*len,
    unsigned short	*reply_port
)
{
    kdp_regions_req_t	*rq = &pkt->regions_req;
    size_t		plen = *len;
    kdp_regions_reply_t *rp = &pkt->regions_reply;
    kdp_region_t	*r;	

    if (plen < sizeof (*rq))
	return (FALSE);

    rp->hdr.is_reply = 1;
    rp->hdr.len = sizeof (*rp);

    dprintf(("kdp_regions\n"));

    r = rp->regions;
    rp->nregions = 0;

    r->address = 0;
    r->nbytes = 0xffffffff;

    r->protection = VM_PROT_ALL; r++; rp->nregions++;
    
    rp->hdr.len += rp->nregions * sizeof (kdp_region_t);
    
    *reply_port = kdp.reply_port;
    *len = rp->hdr.len;
    
    return (TRUE);
}