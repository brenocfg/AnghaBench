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
typedef  size_t u32 ;
struct tgt_ring {scalar_t__* tr_pages; } ;
struct tgt_event {int dummy; } ;

/* Variables and functions */
 size_t TGT_EVENT_PER_PAGE ; 

__attribute__((used)) static struct tgt_event *tgt_head_event(struct tgt_ring *ring, u32 idx)
{
	u32 pidx, off;

	pidx = idx / TGT_EVENT_PER_PAGE;
	off = idx % TGT_EVENT_PER_PAGE;

	return (struct tgt_event *)
		(ring->tr_pages[pidx] + sizeof(struct tgt_event) * off);
}