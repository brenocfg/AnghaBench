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
struct nlm_cookie {scalar_t__ data; } ;
struct nlm_block {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  dprintk (char*,unsigned int,scalar_t__) ; 
 scalar_t__ nlm_lck_denied_grace_period ; 
 struct nlm_block* nlmsvc_find_block (struct nlm_cookie*) ; 
 int /*<<< orphan*/  nlmsvc_insert_block (struct nlm_block*,int) ; 
 int /*<<< orphan*/  nlmsvc_release_block (struct nlm_block*) ; 
 int /*<<< orphan*/  nlmsvc_unlink_block (struct nlm_block*) ; 

void
nlmsvc_grant_reply(struct nlm_cookie *cookie, __be32 status)
{
	struct nlm_block	*block;

	dprintk("grant_reply: looking for cookie %x, s=%d \n",
		*(unsigned int *)(cookie->data), status);
	if (!(block = nlmsvc_find_block(cookie)))
		return;

	if (block) {
		if (status == nlm_lck_denied_grace_period) {
			/* Try again in a couple of seconds */
			nlmsvc_insert_block(block, 10 * HZ);
		} else {
			/* Lock is now held by client, or has been rejected.
			 * In both cases, the block should be removed. */
			nlmsvc_unlink_block(block);
		}
	}
	nlmsvc_release_block(block);
}