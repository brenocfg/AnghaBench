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
 size_t CFAG12864B_ADDRESS (unsigned char,unsigned char) ; 
 int CFAG12864B_BIT (unsigned char) ; 
 unsigned char CFAG12864B_BPB ; 
 scalar_t__ CFAG12864B_CHECK (unsigned char,unsigned char) ; 
 int* cfag12864b_buffer ; 

__attribute__((used)) static unsigned char cfag12864b_isset(unsigned char x, unsigned char y)
{
	if (CFAG12864B_CHECK(x, y))
		if (cfag12864b_buffer[CFAG12864B_ADDRESS(x, y)] &
			CFAG12864B_BIT(x % CFAG12864B_BPB))
			return 1;

	return 0;
}