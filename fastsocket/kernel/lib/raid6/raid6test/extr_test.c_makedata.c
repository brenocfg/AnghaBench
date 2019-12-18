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
 int NDISKS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/ ** data ; 
 int /*<<< orphan*/ ** dataptrs ; 
 int /*<<< orphan*/  rand () ; 

__attribute__((used)) static void makedata(void)
{
	int i, j;

	for (i = 0; i < NDISKS; i++) {
		for (j = 0; j < PAGE_SIZE; j++)
			data[i][j] = rand();

		dataptrs[i] = data[i];
	}
}