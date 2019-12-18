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
typedef  int /*<<< orphan*/  DTEntry ;

/* Variables and functions */
 int /*<<< orphan*/  DTInitialized ; 
 scalar_t__ DTRootNode ; 
 int find_entry (char const*,char const*,int /*<<< orphan*/ *) ; 
 int kError ; 
 char* startingP ; 

int DTFindEntry(const char *propName, const char *propValue, DTEntry *entryH)
{
	if (!DTInitialized) {
		return kError;
	}

	startingP = (char *)DTRootNode;
	return(find_entry(propName, propValue, entryH));
}