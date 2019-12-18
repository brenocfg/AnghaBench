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
 int MAX_NODES ; 
 int highest_node ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int strtoul (char*,char**,int) ; 

__attribute__((used)) static void decode_numa_list(int *numa, char *t)
{
	int node;
	int nr;

	memset(numa, 0, MAX_NODES * sizeof(int));

	if (!t)
		return;

	while (*t == 'N') {
		t++;
		node = strtoul(t, &t, 10);
		if (*t == '=') {
			t++;
			nr = strtoul(t, &t, 10);
			numa[node] = nr;
			if (node > highest_node)
				highest_node = node;
		}
		while (*t == ' ')
			t++;
	}
}