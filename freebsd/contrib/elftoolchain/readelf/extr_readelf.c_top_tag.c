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
typedef  int /*<<< orphan*/  s_top_tag ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
top_tag(unsigned int tag)
{
	static char s_top_tag[32];

	switch (tag) {
	case 1: return "File Attributes";
	case 2: return "Section Attributes";
	case 3: return "Symbol Attributes";
	default:
		snprintf(s_top_tag, sizeof(s_top_tag), "Unknown tag: %u", tag);
		return (s_top_tag);
	}
}