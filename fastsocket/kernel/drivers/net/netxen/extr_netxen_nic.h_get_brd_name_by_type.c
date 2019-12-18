#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ brdtype; int /*<<< orphan*/  short_name; } ;

/* Variables and functions */
 int NUM_SUPPORTED_BOARDS ; 
 TYPE_1__* netxen_boards ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void get_brd_name_by_type(u32 type, char *name)
{
	int i, found = 0;
	for (i = 0; i < NUM_SUPPORTED_BOARDS; ++i) {
		if (netxen_boards[i].brdtype == type) {
			strcpy(name, netxen_boards[i].short_name);
			found = 1;
			break;
		}

	}
	if (!found)
		name = "Unknown";
}