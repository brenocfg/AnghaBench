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
typedef  int /*<<< orphan*/  stbtt__edge ;

/* Variables and functions */
 int /*<<< orphan*/  stbtt__sort_edges_ins_sort (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stbtt__sort_edges_quicksort (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void stbtt__sort_edges(stbtt__edge *p, int n)
{
   stbtt__sort_edges_quicksort(p, n);
   stbtt__sort_edges_ins_sort(p, n);
}