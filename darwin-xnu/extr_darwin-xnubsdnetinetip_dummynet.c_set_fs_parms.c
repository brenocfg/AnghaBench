#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dn_flow_set {int flags_fs; int qsize; int /*<<< orphan*/  flow_mask; int /*<<< orphan*/  plr; } ;

/* Variables and functions */
 int DN_IS_RED ; 
 int DN_QSIZE_IS_BYTES ; 
 int /*<<< orphan*/  config_red (struct dn_flow_set*,struct dn_flow_set*) ; 

__attribute__((used)) static void
set_fs_parms(struct dn_flow_set *x, struct dn_flow_set *src)
{
    x->flags_fs = src->flags_fs;
    x->qsize = src->qsize;
    x->plr = src->plr;
    x->flow_mask = src->flow_mask;
    if (x->flags_fs & DN_QSIZE_IS_BYTES) {
	if (x->qsize > 1024*1024)
	    x->qsize = 1024*1024 ;
    } else {
	if (x->qsize == 0)
	    x->qsize = 50 ;
	if (x->qsize > 100)
	    x->qsize = 50 ;
    }
    /* configuring RED */
    if ( x->flags_fs & DN_IS_RED )
	config_red(src, x) ;    /* XXX should check errors */
}