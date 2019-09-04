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
#define  COALITION_TYPE_JETSAM 129 
#define  COALITION_TYPE_RESOURCE 128 

__attribute__((used)) static const char *coal_type_str(int type)
{
	switch(type) {
	case COALITION_TYPE_RESOURCE:
		return "RESOURCE";
	case COALITION_TYPE_JETSAM:
		return "JETSAM";
	default:
		return "<unknown>";
	}
}