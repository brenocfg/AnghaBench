#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct user_key_payload {size_t datalen; int /*<<< orphan*/  rcu; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {struct user_key_payload* data; } ;
struct key {scalar_t__ expiry; TYPE_1__ payload; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int key_payload_reserve (struct key*,size_t) ; 
 struct user_key_payload* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  rcu_assign_keypointer (struct key*,struct user_key_payload*) ; 
 int /*<<< orphan*/  user_update_rcu_disposal ; 

int user_update(struct key *key, const void *data, size_t datalen)
{
	struct user_key_payload *upayload, *zap;
	int ret;

	ret = -EINVAL;
	if (datalen <= 0 || datalen > 32767 || !data)
		goto error;

	/* construct a replacement payload */
	ret = -ENOMEM;
	upayload = kmalloc(sizeof(*upayload) + datalen, GFP_KERNEL);
	if (!upayload)
		goto error;

	upayload->datalen = datalen;
	memcpy(upayload->data, data, datalen);

	/* check the quota and attach the new data */
	zap = upayload;

	ret = key_payload_reserve(key, datalen);

	if (ret == 0) {
		/* attach the new data, displacing the old */
		zap = key->payload.data;
		rcu_assign_keypointer(key, upayload);
		key->expiry = 0;
	}

	if (zap)
		call_rcu(&zap->rcu, user_update_rcu_disposal);

error:
	return ret;
}