#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_12__ {int* TupleData; int TupleDataLen; } ;
typedef  TYPE_2__ tuple_t ;
struct TYPE_16__ {int nwin; TYPE_1__* win; } ;
struct TYPE_17__ {scalar_t__ IRQInfo1; } ;
struct TYPE_18__ {scalar_t__ nwin; } ;
struct TYPE_14__ {scalar_t__ reserved; scalar_t__ ready; scalar_t__ wait; } ;
struct TYPE_15__ {scalar_t__ present; } ;
struct TYPE_13__ {int index; int flags; int interface; int subtuples; TYPE_6__ mem; TYPE_7__ irq; TYPE_8__ io; TYPE_4__ timing; TYPE_5__ vpp2; TYPE_5__ vpp1; TYPE_5__ vcc; } ;
typedef  TYPE_3__ cistpl_cftable_entry_t ;
struct TYPE_11__ {int len; int card_addr; int /*<<< orphan*/  host_addr; } ;

/* Variables and functions */
 int CISTPL_CFTABLE_BVDS ; 
 int CISTPL_CFTABLE_DEFAULT ; 
 int CISTPL_CFTABLE_MWAIT ; 
 int CISTPL_CFTABLE_RDYBSY ; 
 int CISTPL_CFTABLE_WP ; 
 int EINVAL ; 
 int get_unaligned_le16 (int*) ; 
 int* parse_io (int*,int*,TYPE_8__*) ; 
 int* parse_irq (int*,int*,TYPE_7__*) ; 
 int* parse_mem (int*,int*,TYPE_6__*) ; 
 int* parse_power (int*,int*,TYPE_5__*) ; 
 int* parse_timing (int*,int*,TYPE_4__*) ; 

__attribute__((used)) static int parse_cftable_entry(tuple_t *tuple,
			       cistpl_cftable_entry_t *entry)
{
    u_char *p, *q, features;

    p = tuple->TupleData;
    q = p + tuple->TupleDataLen;
    entry->index = *p & 0x3f;
    entry->flags = 0;
    if (*p & 0x40)
	entry->flags |= CISTPL_CFTABLE_DEFAULT;
    if (*p & 0x80) {
	if (++p == q)
		return -EINVAL;
	if (*p & 0x10)
	    entry->flags |= CISTPL_CFTABLE_BVDS;
	if (*p & 0x20)
	    entry->flags |= CISTPL_CFTABLE_WP;
	if (*p & 0x40)
	    entry->flags |= CISTPL_CFTABLE_RDYBSY;
	if (*p & 0x80)
	    entry->flags |= CISTPL_CFTABLE_MWAIT;
	entry->interface = *p & 0x0f;
    } else
	entry->interface = 0;

    /* Process optional features */
    if (++p == q)
	    return -EINVAL;
    features = *p; p++;

    /* Power options */
    if ((features & 3) > 0) {
	p = parse_power(p, q, &entry->vcc);
	if (p == NULL)
		return -EINVAL;
    } else
	entry->vcc.present = 0;
    if ((features & 3) > 1) {
	p = parse_power(p, q, &entry->vpp1);
	if (p == NULL)
		return -EINVAL;
    } else
	entry->vpp1.present = 0;
    if ((features & 3) > 2) {
	p = parse_power(p, q, &entry->vpp2);
	if (p == NULL)
		return -EINVAL;
    } else
	entry->vpp2.present = 0;

    /* Timing options */
    if (features & 0x04) {
	p = parse_timing(p, q, &entry->timing);
	if (p == NULL)
		return -EINVAL;
    } else {
	entry->timing.wait = 0;
	entry->timing.ready = 0;
	entry->timing.reserved = 0;
    }
    
    /* I/O window options */
    if (features & 0x08) {
	p = parse_io(p, q, &entry->io);
	if (p == NULL)
		return -EINVAL;
    } else
	entry->io.nwin = 0;
    
    /* Interrupt options */
    if (features & 0x10) {
	p = parse_irq(p, q, &entry->irq);
	if (p == NULL)
		return -EINVAL;
    } else
	entry->irq.IRQInfo1 = 0;

    switch (features & 0x60) {
    case 0x00:
	entry->mem.nwin = 0;
	break;
    case 0x20:
	entry->mem.nwin = 1;
	entry->mem.win[0].len = get_unaligned_le16(p) << 8;
	entry->mem.win[0].card_addr = 0;
	entry->mem.win[0].host_addr = 0;
	p += 2;
	if (p > q)
		return -EINVAL;
	break;
    case 0x40:
	entry->mem.nwin = 1;
	entry->mem.win[0].len = get_unaligned_le16(p) << 8;
	entry->mem.win[0].card_addr = get_unaligned_le16(p + 2) << 8;
	entry->mem.win[0].host_addr = 0;
	p += 4;
	if (p > q)
		return -EINVAL;
	break;
    case 0x60:
	p = parse_mem(p, q, &entry->mem);
	if (p == NULL)
		return -EINVAL;
	break;
    }

    /* Misc features */
    if (features & 0x80) {
	if (p == q)
		return -EINVAL;
	entry->flags |= (*p << 8);
	while (*p & 0x80)
	    if (++p == q)
		    return -EINVAL;
	p++;
    }

    entry->subtuples = q-p;
    
    return 0;
}