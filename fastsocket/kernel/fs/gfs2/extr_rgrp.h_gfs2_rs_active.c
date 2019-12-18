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
struct gfs2_blkreserv {int /*<<< orphan*/  rs_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool gfs2_rs_active(struct gfs2_blkreserv *rs)
{
	return rs && !RB_EMPTY_NODE(&rs->rs_node);
}