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
struct fuse_req {int dummy; } ;
struct fuse_conn {int dummy; } ;

/* Variables and functions */
 struct fuse_req* fuse_get_req (struct fuse_conn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct fuse_req *fuse_get_req_nopages(struct fuse_conn *fc)
{
	return fuse_get_req(fc, 0);
}