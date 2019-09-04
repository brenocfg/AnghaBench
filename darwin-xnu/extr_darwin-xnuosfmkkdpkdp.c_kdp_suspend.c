#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kdp_suspend_req_t ;
struct TYPE_6__ {int is_reply; int len; } ;
struct TYPE_7__ {TYPE_1__ hdr; } ;
typedef  TYPE_2__ kdp_suspend_reply_t ;
struct TYPE_8__ {TYPE_2__ suspend_reply; int /*<<< orphan*/  suspend_req; } ;
typedef  TYPE_3__ kdp_pkt_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_9__ {unsigned short reply_port; int /*<<< orphan*/  is_halted; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 TYPE_5__ kdp ; 

__attribute__((used)) static boolean_t
kdp_suspend(
    kdp_pkt_t		*pkt,
    int			*len,
    unsigned short	*reply_port
)
{
    kdp_suspend_req_t	*rq = &pkt->suspend_req;
    size_t		plen = *len;
    kdp_suspend_reply_t *rp = &pkt->suspend_reply;

    if (plen < sizeof (*rq))
	return (FALSE);

    rp->hdr.is_reply = 1;
    rp->hdr.len = sizeof (*rp);

    dprintf(("kdp_suspend\n"));

    kdp.is_halted = TRUE;
    
    *reply_port = kdp.reply_port;
    *len = rp->hdr.len;
    
    return (TRUE);
}