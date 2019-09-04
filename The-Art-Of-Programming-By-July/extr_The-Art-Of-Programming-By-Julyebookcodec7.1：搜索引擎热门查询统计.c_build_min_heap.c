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
typedef  int /*<<< orphan*/  node_has_space ;

/* Variables and functions */
 int /*<<< orphan*/  sift_down (int /*<<< orphan*/ *,int,int) ; 

void build_min_heap(node_has_space heap[], int len)
{
	if (heap == NULL)
		return;

	int index = len / 2;
	for (int i = index; i >= 1; i--)
		sift_down(heap, i, len);
}