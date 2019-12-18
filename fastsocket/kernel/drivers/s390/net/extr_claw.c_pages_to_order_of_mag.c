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

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
pages_to_order_of_mag(int num_of_pages)
{
	int	order_of_mag=1;		/* assume 2 pages */
	int	nump;

	CLAW_DBF_TEXT_(5, trace, "pages%d", num_of_pages);
	if (num_of_pages == 1)   {return 0; }  /* magnitude of 0 = 1 page */
	/* 512 pages = 2Meg on 4k page systems */
	if (num_of_pages >= 512) {return 9; }
	/* we have two or more pages order is at least 1 */
	for (nump=2 ;nump <= 512;nump*=2) {
	  if (num_of_pages <= nump)
		  break;
	  order_of_mag +=1;
	}
	if (order_of_mag > 9) { order_of_mag = 9; }  /* I know it's paranoid */
	CLAW_DBF_TEXT_(5, trace, "mag%d", order_of_mag);
	return order_of_mag;
}