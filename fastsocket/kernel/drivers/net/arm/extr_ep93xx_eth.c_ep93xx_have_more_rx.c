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
struct ep93xx_rstat {int rstat0; int rstat1; } ;
struct ep93xx_priv {int rx_pointer; TYPE_1__* descs; } ;
struct TYPE_2__ {struct ep93xx_rstat* rstat; } ;

/* Variables and functions */
 int RSTAT0_RFP ; 
 int RSTAT1_RFP ; 

__attribute__((used)) static int ep93xx_have_more_rx(struct ep93xx_priv *ep)
{
	struct ep93xx_rstat *rstat = ep->descs->rstat + ep->rx_pointer;
	return !!((rstat->rstat0 & RSTAT0_RFP) && (rstat->rstat1 & RSTAT1_RFP));
}