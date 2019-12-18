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
struct nfs_iostats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (struct nfs_iostats*) ; 

__attribute__((used)) static inline void nfs_free_iostats(struct nfs_iostats *stats)
{
	if (stats != NULL)
		free_percpu(stats);
}