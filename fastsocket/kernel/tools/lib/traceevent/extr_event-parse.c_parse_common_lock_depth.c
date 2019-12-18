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
struct pevent {int /*<<< orphan*/  ld_offset; int /*<<< orphan*/  ld_size; } ;

/* Variables and functions */
 int __parse_common (struct pevent*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int parse_common_lock_depth(struct pevent *pevent, void *data)
{
	return __parse_common(pevent, data,
			      &pevent->ld_size, &pevent->ld_offset,
			      "common_lock_depth");
}