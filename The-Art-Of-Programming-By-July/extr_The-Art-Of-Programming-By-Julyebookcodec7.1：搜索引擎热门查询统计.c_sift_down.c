#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ count; char* word; } ;
typedef  TYPE_1__ node_has_space ;

/* Variables and functions */
 int WORDLEN ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  swap (scalar_t__,scalar_t__) ; 

void sift_down(node_has_space heap[], int i, int len)
{
	int min_index = -1;
	int left = 2 * i;
	int right = 2 * i + 1;

	if (left <= len && heap[left].count < heap[i].count)
		min_index = left;
	else
		min_index = i;

	if (right <= len && heap[right].count < heap[min_index].count)
		min_index = right;

	if (min_index != i)
	{
		// 交换结点元素
		swap(heap[i].count, heap[min_index].count);

		char buffer[WORDLEN];
		strcpy(buffer, heap[i].word);
		strcpy(heap[i].word, heap[min_index].word);
		strcpy(heap[min_index].word, buffer);

		sift_down(heap, min_index, len);
	}
}