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
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int list_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) inline static int
EventSetSizeForConnectionList(List *connections)
{
	/* we need space for 2 postgres events in the waitset on top of the connections */
	return list_length(connections) + 2;
}