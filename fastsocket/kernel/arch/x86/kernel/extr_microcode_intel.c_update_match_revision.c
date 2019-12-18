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
struct microcode_header_intel {int rev; } ;

/* Variables and functions */

__attribute__((used)) static inline int
update_match_revision(struct microcode_header_intel *mc_header, int rev)
{
	return (mc_header->rev <= rev) ? 0 : 1;
}