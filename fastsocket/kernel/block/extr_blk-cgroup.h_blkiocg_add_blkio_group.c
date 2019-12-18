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
struct blkio_group {int dummy; } ;
struct blkio_cgroup {int dummy; } ;
typedef  enum blkio_policy_id { ____Placeholder_blkio_policy_id } blkio_policy_id ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */

__attribute__((used)) static inline void blkiocg_add_blkio_group(struct blkio_cgroup *blkcg,
		struct blkio_group *blkg, void *key, dev_t dev,
		enum blkio_policy_id plid) {}