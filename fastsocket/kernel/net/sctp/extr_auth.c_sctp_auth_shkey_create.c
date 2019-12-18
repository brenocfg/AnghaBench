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
struct sctp_shared_key {int /*<<< orphan*/  key_id; int /*<<< orphan*/  key_list; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct sctp_shared_key* kzalloc (int,int /*<<< orphan*/ ) ; 

struct sctp_shared_key *sctp_auth_shkey_create(__u16 key_id, gfp_t gfp)
{
	struct sctp_shared_key *new;

	/* Allocate the shared key container */
	new = kzalloc(sizeof(struct sctp_shared_key), gfp);
	if (!new)
		return NULL;

	INIT_LIST_HEAD(&new->key_list);
	new->key_id = key_id;

	return new;
}