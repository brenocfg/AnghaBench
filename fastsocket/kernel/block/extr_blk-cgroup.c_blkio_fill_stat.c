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
typedef  int /*<<< orphan*/  uint64_t ;
struct cgroup_map_cb {int /*<<< orphan*/  (* fill ) (struct cgroup_map_cb*,char*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  blkio_get_key_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct cgroup_map_cb*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t blkio_fill_stat(char *str, int chars_left, uint64_t val,
				struct cgroup_map_cb *cb, dev_t dev)
{
	blkio_get_key_name(0, dev, str, chars_left, true);
	cb->fill(cb, str, val);
	return val;
}