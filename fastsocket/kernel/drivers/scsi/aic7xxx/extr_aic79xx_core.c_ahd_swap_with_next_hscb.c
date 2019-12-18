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
typedef  int /*<<< orphan*/  uint32_t ;
struct scb {struct map_node* hscb_map; struct hardware_scb* hscb; } ;
struct map_node {int dummy; } ;
struct hardware_scb {int /*<<< orphan*/  hscb_busaddr; int /*<<< orphan*/  next_hscb_busaddr; } ;
struct TYPE_2__ {struct scb** scbindex; } ;
struct ahd_softc {TYPE_1__ scb_data; struct map_node* next_queued_hscb_map; struct hardware_scb* next_queued_hscb; } ;

/* Variables and functions */
 size_t SCB_GET_TAG (struct scb*) ; 
 int /*<<< orphan*/  memcpy (struct hardware_scb*,struct hardware_scb*,int) ; 

__attribute__((used)) static void
ahd_swap_with_next_hscb(struct ahd_softc *ahd, struct scb *scb)
{
	struct	 hardware_scb *q_hscb;
	struct	 map_node *q_hscb_map;
	uint32_t saved_hscb_busaddr;

	/*
	 * Our queuing method is a bit tricky.  The card
	 * knows in advance which HSCB (by address) to download,
	 * and we can't disappoint it.  To achieve this, the next
	 * HSCB to download is saved off in ahd->next_queued_hscb.
	 * When we are called to queue "an arbitrary scb",
	 * we copy the contents of the incoming HSCB to the one
	 * the sequencer knows about, swap HSCB pointers and
	 * finally assign the SCB to the tag indexed location
	 * in the scb_array.  This makes sure that we can still
	 * locate the correct SCB by SCB_TAG.
	 */
	q_hscb = ahd->next_queued_hscb;
	q_hscb_map = ahd->next_queued_hscb_map;
	saved_hscb_busaddr = q_hscb->hscb_busaddr;
	memcpy(q_hscb, scb->hscb, sizeof(*scb->hscb));
	q_hscb->hscb_busaddr = saved_hscb_busaddr;
	q_hscb->next_hscb_busaddr = scb->hscb->hscb_busaddr;

	/* Now swap HSCB pointers. */
	ahd->next_queued_hscb = scb->hscb;
	ahd->next_queued_hscb_map = scb->hscb_map;
	scb->hscb = q_hscb;
	scb->hscb_map = q_hscb_map;

	/* Now define the mapping from tag to SCB in the scbindex */
	ahd->scb_data.scbindex[SCB_GET_TAG(scb)] = scb;
}