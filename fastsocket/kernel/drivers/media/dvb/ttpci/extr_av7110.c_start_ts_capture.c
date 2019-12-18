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
struct av7110 {int feeding1; int /*<<< orphan*/  dev; scalar_t__ ttbp; int /*<<< orphan*/  grabbing; } ;

/* Variables and functions */
 int MASK_04 ; 
 int /*<<< orphan*/  MASK_10 ; 
 int MASK_20 ; 
 int /*<<< orphan*/  MC1 ; 
 int /*<<< orphan*/  SAA7146_IER_ENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAA7146_ISR_CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_BUFLEN ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int start_ts_capture(struct av7110 *budget)
{
	dprintk(2, "budget: %p\n", budget);

	if (budget->feeding1)
		return ++budget->feeding1;
	memset(budget->grabbing, 0x00, TS_BUFLEN);
	budget->ttbp = 0;
	SAA7146_ISR_CLEAR(budget->dev, MASK_10);  /* VPE */
	SAA7146_IER_ENABLE(budget->dev, MASK_10); /* VPE */
	saa7146_write(budget->dev, MC1, (MASK_04 | MASK_20)); /* DMA3 on */
	return ++budget->feeding1;
}