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
struct super_block {int dummy; } ;
struct fuse_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_conn_kill (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_conn_put (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_send_destroy (struct fuse_conn*) ; 
 struct fuse_conn* get_fuse_conn_super (struct super_block*) ; 

__attribute__((used)) static void fuse_put_super(struct super_block *sb)
{
	struct fuse_conn *fc = get_fuse_conn_super(sb);

	fuse_send_destroy(fc);
	fuse_conn_kill(fc);
	fuse_conn_put(fc);
}