#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  other; } ;
struct ndrv_demux_desc {scalar_t__ type; int length; TYPE_1__ data; } ;
struct ifnet_demux_desc {scalar_t__ type; int datalen; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ DLIL_DESC_ETYPE2 ; 
 int EINVAL ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  bzero (struct ifnet_demux_desc*,int) ; 

int
ndrv_to_ifnet_demux(struct ndrv_demux_desc* ndrv, struct ifnet_demux_desc* ifdemux)
{
    bzero(ifdemux, sizeof(*ifdemux));

    if (ndrv->type < DLIL_DESC_ETYPE2)
    {
        /* using old "type", not supported */
        return ENOTSUP;
    }

    if (ndrv->length > 28)
    {
        return EINVAL;
    }

    ifdemux->type = ndrv->type;
    ifdemux->data = ndrv->data.other;
    ifdemux->datalen = ndrv->length;

    return 0;
}