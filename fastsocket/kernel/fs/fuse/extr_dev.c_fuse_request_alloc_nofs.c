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

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct fuse_req* __fuse_request_alloc (unsigned int,int /*<<< orphan*/ ) ; 

struct fuse_req *fuse_request_alloc_nofs(unsigned npages)
{
	return __fuse_request_alloc(npages, GFP_NOFS);
}