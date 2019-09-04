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
struct TYPE_6__ {int is_reply; int len; } ;
struct TYPE_8__ {TYPE_1__ hdr; int /*<<< orphan*/  hostinfo; } ;
struct TYPE_7__ {TYPE_3__ hostinfo_reply; int /*<<< orphan*/  hostinfo_req; } ;
typedef  TYPE_2__ kdp_pkt_t ;
typedef  int /*<<< orphan*/  kdp_hostinfo_req_t ;
typedef  TYPE_3__ kdp_hostinfo_reply_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_9__ {unsigned short reply_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 TYPE_5__ kdp ; 
 int /*<<< orphan*/  kdp_machine_hostinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static boolean_t
kdp_hostinfo(
    kdp_pkt_t		*pkt,
    int			*len,
    unsigned short	*reply_port
)
{
    kdp_hostinfo_req_t	*rq = &pkt->hostinfo_req;
    size_t		plen = *len;
    kdp_hostinfo_reply_t *rp = &pkt->hostinfo_reply;

    if (plen < sizeof (*rq))
	return (FALSE);

    dprintf(("kdp_hostinfo\n"));

    rp->hdr.is_reply = 1;
    rp->hdr.len = sizeof (*rp);

    kdp_machine_hostinfo(&rp->hostinfo);

    *reply_port = kdp.reply_port;
    *len = rp->hdr.len;
    
    return (TRUE);
}