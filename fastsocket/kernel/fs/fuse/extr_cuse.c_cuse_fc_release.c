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
struct fuse_conn {int dummy; } ;
struct cuse_conn {int dummy; } ;

/* Variables and functions */
 struct cuse_conn* fc_to_cc (struct fuse_conn*) ; 
 int /*<<< orphan*/  kfree (struct cuse_conn*) ; 

__attribute__((used)) static void cuse_fc_release(struct fuse_conn *fc)
{
	struct cuse_conn *cc = fc_to_cc(fc);
	kfree(cc);
}