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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct tidaw {scalar_t__ addr; int /*<<< orphan*/  count; int /*<<< orphan*/  flags; } ;
struct tcw {int dummy; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct tidaw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tcw_get_data (struct tcw*) ; 

struct tidaw *tcw_add_tidaw(struct tcw *tcw, int num_tidaws, u8 flags,
			    void *addr, u32 count)
{
	struct tidaw *tidaw;

	/* Add tidaw to tidaw-list. */
	tidaw = ((struct tidaw *) tcw_get_data(tcw)) + num_tidaws;
	memset(tidaw, 0, sizeof(struct tidaw));
	tidaw->flags = flags;
	tidaw->count = count;
	tidaw->addr = (u64) ((addr_t) addr);
	return tidaw;
}