#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct atm_dev {int dummy; } ;
typedef  int loff_t ;
struct TYPE_9__ {int pending; int maximum; int high; int filled; } ;
typedef  TYPE_2__ amb_txq ;
struct TYPE_8__ {int /*<<< orphan*/  unused; int /*<<< orphan*/  aborted; int /*<<< orphan*/  toolong; int /*<<< orphan*/  badcrc; int /*<<< orphan*/  error; int /*<<< orphan*/  ok; } ;
struct TYPE_10__ {TYPE_1__ rx; int /*<<< orphan*/  tx_ok; } ;
typedef  TYPE_3__ amb_stats ;
struct TYPE_11__ {int pending; int maximum; int buffers_wanted; int low; int emptied; int buffer_size; } ;
typedef  TYPE_4__ amb_rxq ;
struct TYPE_13__ {int pending; int high; int maximum; } ;
struct TYPE_12__ {TYPE_4__* rxq; TYPE_2__ txq; TYPE_6__ cq; TYPE_3__ stats; } ;
typedef  TYPE_5__ amb_dev ;
typedef  TYPE_6__ amb_cq ;

/* Variables and functions */
 TYPE_5__* AMB_DEV (struct atm_dev*) ; 
 int /*<<< orphan*/  DBG_FLOW ; 
 unsigned char NUM_RX_POOLS ; 
 int /*<<< orphan*/  PRINTD (int /*<<< orphan*/ ,char*) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static int amb_proc_read (struct atm_dev * atm_dev, loff_t * pos, char * page) {
  amb_dev * dev = AMB_DEV (atm_dev);
  int left = *pos;
  unsigned char pool;
  
  PRINTD (DBG_FLOW, "amb_proc_read");
  
  /* more diagnostics here? */
  
  if (!left--) {
    amb_stats * s = &dev->stats;
    return sprintf (page,
		    "frames: TX OK %lu, RX OK %lu, RX bad %lu "
		    "(CRC %lu, long %lu, aborted %lu, unused %lu).\n",
		    s->tx_ok, s->rx.ok, s->rx.error,
		    s->rx.badcrc, s->rx.toolong,
		    s->rx.aborted, s->rx.unused);
  }
  
  if (!left--) {
    amb_cq * c = &dev->cq;
    return sprintf (page, "cmd queue [cur/hi/max]: %u/%u/%u. ",
		    c->pending, c->high, c->maximum);
  }
  
  if (!left--) {
    amb_txq * t = &dev->txq;
    return sprintf (page, "TX queue [cur/max high full]: %u/%u %u %u.\n",
		    t->pending, t->maximum, t->high, t->filled);
  }
  
  if (!left--) {
    unsigned int count = sprintf (page, "RX queues [cur/max/req low empty]:");
    for (pool = 0; pool < NUM_RX_POOLS; ++pool) {
      amb_rxq * r = &dev->rxq[pool];
      count += sprintf (page+count, " %u/%u/%u %u %u",
			r->pending, r->maximum, r->buffers_wanted, r->low, r->emptied);
    }
    count += sprintf (page+count, ".\n");
    return count;
  }
  
  if (!left--) {
    unsigned int count = sprintf (page, "RX buffer sizes:");
    for (pool = 0; pool < NUM_RX_POOLS; ++pool) {
      amb_rxq * r = &dev->rxq[pool];
      count += sprintf (page+count, " %u", r->buffer_size);
    }
    count += sprintf (page+count, ".\n");
    return count;
  }
  
#if 0
  if (!left--) {
    // suni block etc?
  }
#endif
  
  return 0;
}