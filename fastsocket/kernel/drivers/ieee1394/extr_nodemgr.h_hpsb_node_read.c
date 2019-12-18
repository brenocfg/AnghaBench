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
typedef  int /*<<< orphan*/  u64 ;
struct node_entry {unsigned int generation; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  quadlet_t ;

/* Variables and functions */
 int hpsb_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static inline int hpsb_node_read(struct node_entry *ne, u64 addr,
				 quadlet_t *buffer, size_t length)
{
	unsigned int g = ne->generation;

	smp_rmb();
	return hpsb_read(ne->host, ne->nodeid, g, addr, buffer, length);
}