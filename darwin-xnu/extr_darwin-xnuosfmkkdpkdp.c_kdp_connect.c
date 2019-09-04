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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_9__ {int is_reply; int len; } ;
struct TYPE_12__ {TYPE_2__ hdr; void* error; } ;
struct TYPE_8__ {scalar_t__ seq; scalar_t__ key; } ;
struct TYPE_11__ {scalar_t__ req_reply_port; scalar_t__ exc_note_port; TYPE_1__ hdr; int /*<<< orphan*/  greeting; } ;
struct TYPE_10__ {TYPE_5__ connect_reply; TYPE_4__ connect_req; } ;
typedef  TYPE_3__ kdp_pkt_t ;
typedef  TYPE_4__ kdp_connect_req_t ;
typedef  TYPE_5__ kdp_connect_reply_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_13__ {scalar_t__ conn_seq; scalar_t__ reply_port; scalar_t__ exception_port; scalar_t__ session_key; scalar_t__ is_conn; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 void* KDPERR_ALREADY_CONNECTED ; 
 void* KDPERR_NO_ERROR ; 
 scalar_t__ KDP_CUR_DB ; 
 scalar_t__ TRUE ; 
 int active_debugger ; 
 scalar_t__ current_debugger ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 TYPE_7__ kdp ; 

__attribute__((used)) static boolean_t
kdp_connect(
    kdp_pkt_t		*pkt,
    int			*len,
    unsigned short	*reply_port
)
{
    kdp_connect_req_t	*rq = &pkt->connect_req;
    size_t		plen = *len;
    kdp_connect_reply_t	*rp = &pkt->connect_reply;
    uint16_t            rport, eport;
    uint32_t            key;
    uint8_t             seq;

    if (plen < sizeof (*rq))
	return (FALSE);

    dprintf(("kdp_connect seq %x greeting %s\n", rq->hdr.seq, rq->greeting));

    rport = rq->req_reply_port;
    eport = rq->exc_note_port;
    key   = rq->hdr.key;
    seq   = rq->hdr.seq;
    if (kdp.is_conn) {
	if ((seq == kdp.conn_seq) &&	/* duplicate request */
            (rport == kdp.reply_port) &&
            (eport == kdp.exception_port) &&
            (key == kdp.session_key))
	    rp->error = KDPERR_NO_ERROR;
	else 
	    rp->error = KDPERR_ALREADY_CONNECTED;
    }
    else { 
	kdp.reply_port     = rport;
	kdp.exception_port = eport;
	kdp.is_conn        = TRUE;
	kdp.conn_seq       = seq;
        kdp.session_key    = key;

	rp->error = KDPERR_NO_ERROR;
    }

    rp->hdr.is_reply = 1;
    rp->hdr.len = sizeof (*rp);
    
    *reply_port = rport;
    *len = rp->hdr.len;
    
    if (current_debugger == KDP_CUR_DB)    
    	active_debugger=1;

    return (TRUE);
}