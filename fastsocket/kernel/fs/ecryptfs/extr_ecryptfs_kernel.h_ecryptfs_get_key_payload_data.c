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
struct user_key_payload {scalar_t__ data; } ;
struct TYPE_2__ {scalar_t__ data; } ;
struct key {TYPE_1__ payload; } ;
struct ecryptfs_auth_tok {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ecryptfs_auth_tok *
ecryptfs_get_key_payload_data(struct key *key)
{
	return (struct ecryptfs_auth_tok *)
		(((struct user_key_payload*)key->payload.data)->data);
}