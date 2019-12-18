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
struct nfs_page {int dummy; } ;
struct nfs_commit_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
pnfs_clear_request_commit(struct nfs_page *req, struct nfs_commit_info *cinfo)
{
	return false;
}