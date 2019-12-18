#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ request; scalar_t__ seq; int /*<<< orphan*/  is_reply; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
typedef  TYPE_2__ kdp_exception_ack_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {scalar_t__ exception_seq; int /*<<< orphan*/  exception_ack_needed; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KDP_EXCEPTION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 TYPE_3__ kdp ; 

boolean_t
kdp_exception_ack(
    unsigned char	*pkt,
    int			len
)
{
    kdp_exception_ack_t	*rq = (kdp_exception_ack_t *)pkt;

    if (((unsigned int) len) < sizeof (*rq))
	return(FALSE);
	
    if (!rq->hdr.is_reply || rq->hdr.request != KDP_EXCEPTION)
    	return(FALSE);
	
    dprintf(("kdp_exception_ack seq %x %x\n", rq->hdr.seq, kdp.exception_seq));
	
    if (rq->hdr.seq == kdp.exception_seq) {
	kdp.exception_ack_needed = FALSE;
	kdp.exception_seq++;
    }
    return(TRUE);
}