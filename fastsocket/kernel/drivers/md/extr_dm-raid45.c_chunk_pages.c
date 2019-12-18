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
 int /*<<< orphan*/  SECTORS_PER_PAGE ; 
 int dm_div_up (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned chunk_pages(unsigned sectors)
{
	return dm_div_up(sectors, SECTORS_PER_PAGE);
}