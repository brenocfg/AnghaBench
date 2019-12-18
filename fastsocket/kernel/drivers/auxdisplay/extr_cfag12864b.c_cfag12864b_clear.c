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
 unsigned char CFAG12864B_ADDRESSES ; 
 unsigned char CFAG12864B_PAGES ; 
 int /*<<< orphan*/  cfag12864b_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfag12864b_page (unsigned char) ; 
 int /*<<< orphan*/  cfag12864b_setcontrollers (int,int) ; 
 int /*<<< orphan*/  cfag12864b_writebyte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfag12864b_clear(void)
{
	unsigned char i, j;

	cfag12864b_setcontrollers(1, 1);
	for (i = 0; i < CFAG12864B_PAGES; i++) {
		cfag12864b_page(i);
		cfag12864b_address(0);
		for (j = 0; j < CFAG12864B_ADDRESSES; j++)
			cfag12864b_writebyte(0);
	}
}