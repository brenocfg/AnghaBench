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
struct node_entry {scalar_t__ generation; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 scalar_t__ get_hpsb_generation (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int hpsb_node_entry_valid(struct node_entry *ne)
{
	return ne->generation == get_hpsb_generation(ne->host);
}