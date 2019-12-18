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
typedef  size_t SelectedState ;

/* Variables and functions */
 size_t SelectedState_STANDBY ; 

__attribute__((used)) static __inline__ const char *
SelectedStateString(SelectedState s)
{
    static const char * names[] = { "UNSELECTED", "SELECTED", "STANDBY" };

    if (s <= SelectedState_STANDBY) {
	return (names[s]);
    }
    return ("<unknown>");
}