#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; scalar_t__ key; int /*<<< orphan*/  seq; scalar_t__ is_reply; int /*<<< orphan*/  request; } ;
struct TYPE_7__ {int n_exc_info; TYPE_2__ hdr; TYPE_1__* exc_info; } ;
typedef  TYPE_3__ kdp_exception_t ;
typedef  int /*<<< orphan*/  kdp_exc_info_t ;
struct TYPE_8__ {unsigned short exception_port; int /*<<< orphan*/  exception_ack_needed; int /*<<< orphan*/  exception_seq; } ;
struct TYPE_5__ {unsigned int exception; unsigned int code; unsigned int subcode; scalar_t__ cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  KDP_EXCEPTION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 TYPE_4__ kdp ; 

void
kdp_exception(
    unsigned char	*pkt,
    int	*len,
    unsigned short	*remote_port,
    unsigned int	exception,
    unsigned int	code,
    unsigned int	subcode
)
{
    kdp_exception_t	*rq = (kdp_exception_t *)pkt;

    rq->hdr.request = KDP_EXCEPTION;
    rq->hdr.is_reply = 0;
    rq->hdr.seq = kdp.exception_seq;
    rq->hdr.key = 0;
    rq->hdr.len = sizeof (*rq);
    
    rq->n_exc_info = 1;
    rq->exc_info[0].cpu = 0;
    rq->exc_info[0].exception = exception;
    rq->exc_info[0].code = code;
    rq->exc_info[0].subcode = subcode;
    
    rq->hdr.len += rq->n_exc_info * sizeof (kdp_exc_info_t);
    
    bcopy((char *)rq, (char *)pkt, rq->hdr.len);

    kdp.exception_ack_needed = TRUE;
    
    *remote_port = kdp.exception_port;
    *len = rq->hdr.len;
}