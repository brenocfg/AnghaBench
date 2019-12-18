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
struct aic7xxx_host {int /*<<< orphan*/  flags; TYPE_1__* scb_data; } ;
struct TYPE_2__ {int maxhscbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_PAGESCBS ; 
 int AIC7XXX_MAXSCB ; 
 scalar_t__ FREE_SCBH ; 
 scalar_t__ SCBPTR ; 
 scalar_t__ SCB_BUSYTARGETS ; 
 scalar_t__ SCB_CONTROL ; 
 int SCB_LIST_NULL ; 
 scalar_t__ SCB_NEXT ; 
 scalar_t__ SCB_TAG ; 
 int aic_inb (struct aic7xxx_host*,scalar_t__) ; 
 int /*<<< orphan*/  aic_outb (struct aic7xxx_host*,int,scalar_t__) ; 

__attribute__((used)) static void
detect_maxscb(struct aic7xxx_host *p)
{
  int i;

  /*
   * It's possible that we've already done this for multichannel
   * adapters.
   */
  if (p->scb_data->maxhscbs == 0)
  {
    /*
     * We haven't initialized the SCB settings yet.  Walk the SCBs to
     * determince how many there are.
     */
    aic_outb(p, 0, FREE_SCBH);

    for (i = 0; i < AIC7XXX_MAXSCB; i++)
    {
      aic_outb(p, i, SCBPTR);
      aic_outb(p, i, SCB_CONTROL);
      if (aic_inb(p, SCB_CONTROL) != i)
        break;
      aic_outb(p, 0, SCBPTR);
      if (aic_inb(p, SCB_CONTROL) != 0)
        break;

      aic_outb(p, i, SCBPTR);
      aic_outb(p, 0, SCB_CONTROL);   /* Clear the control byte. */
      aic_outb(p, i + 1, SCB_NEXT);  /* Set the next pointer. */
      aic_outb(p, SCB_LIST_NULL, SCB_TAG);  /* Make the tag invalid. */
      aic_outb(p, SCB_LIST_NULL, SCB_BUSYTARGETS);  /* no busy untagged */
      aic_outb(p, SCB_LIST_NULL, SCB_BUSYTARGETS+1);/* targets active yet */
      aic_outb(p, SCB_LIST_NULL, SCB_BUSYTARGETS+2);
      aic_outb(p, SCB_LIST_NULL, SCB_BUSYTARGETS+3);
    }

    /* Make sure the last SCB terminates the free list. */
    aic_outb(p, i - 1, SCBPTR);
    aic_outb(p, SCB_LIST_NULL, SCB_NEXT);

    /* Ensure we clear the first (0) SCBs control byte. */
    aic_outb(p, 0, SCBPTR);
    aic_outb(p, 0, SCB_CONTROL);

    p->scb_data->maxhscbs = i;
    /*
     * Use direct indexing instead for speed
     */
    if ( i == AIC7XXX_MAXSCB )
      p->flags &= ~AHC_PAGESCBS;
  }

}