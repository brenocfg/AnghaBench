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
struct toshoboe_cb {int dummy; } ;

/* Variables and functions */
 int CONFIG0H_DMA_ON ; 
 int /*<<< orphan*/  OBOE_CONFIG0H ; 
 int /*<<< orphan*/  OBOE_ENABLEH ; 
 int OBOE_ENABLEH_PHYANDCLOCK ; 
 int /*<<< orphan*/  OUTB (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROMPT ; 

__attribute__((used)) static void
toshoboe_start_DMA (struct toshoboe_cb *self, int opts)
{
  OUTB (0x0, OBOE_ENABLEH);
  OUTB (CONFIG0H_DMA_ON | opts,  OBOE_CONFIG0H);
  OUTB (OBOE_ENABLEH_PHYANDCLOCK, OBOE_ENABLEH);
  PROMPT;
}