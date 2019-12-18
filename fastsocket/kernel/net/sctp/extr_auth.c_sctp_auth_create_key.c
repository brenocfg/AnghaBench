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
struct sctp_auth_bytes {int len; int /*<<< orphan*/  refcnt; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int __u32 ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  SCTP_DBG_OBJCNT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  keys ; 
 struct sctp_auth_bytes* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_auth_bytes *sctp_auth_create_key(__u32 key_len, gfp_t gfp)
{
	struct sctp_auth_bytes *key;

	/* Verify that we are not going to overflow INT_MAX */
	if ((INT_MAX - key_len) < sizeof(struct sctp_auth_bytes))
		return NULL;

	/* Allocate the shared key */
	key = kmalloc(sizeof(struct sctp_auth_bytes) + key_len, gfp);
	if (!key)
		return NULL;

	key->len = key_len;
	atomic_set(&key->refcnt, 1);
	SCTP_DBG_OBJCNT_INC(keys);

	return key;
}