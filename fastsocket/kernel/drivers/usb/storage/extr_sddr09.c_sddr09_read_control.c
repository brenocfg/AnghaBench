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
struct us_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_SHIFT ; 
 int /*<<< orphan*/  US_DEBUGP (char*,unsigned long,unsigned int) ; 
 int sddr09_read21 (struct us_data*,unsigned long,unsigned int,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int
sddr09_read_control(struct us_data *us,
		unsigned long address,
		unsigned int blocks,
		unsigned char *content,
		int use_sg) {

	US_DEBUGP("Read control address %lu, blocks %d\n",
		address, blocks);

	return sddr09_read21(us, address, blocks,
			     CONTROL_SHIFT, content, use_sg);
}