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
struct netfs_cmd {int id; int /*<<< orphan*/  size; } ;
struct netfs_state {int /*<<< orphan*/  data; struct netfs_cmd cmd; } ;

/* Variables and functions */
 int EINVAL ; 
#define  POHMELFS_CRYPTO_CAPABILITIES 129 
#define  POHMELFS_ROOT_CAPABILITIES 128 
 int pohmelfs_crypto_cap_response (struct netfs_state*) ; 
 int pohmelfs_data_recv (struct netfs_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pohmelfs_root_cap_response (struct netfs_state*) ; 

__attribute__((used)) static int pohmelfs_capabilities_response(struct netfs_state *st)
{
	struct netfs_cmd *cmd = &st->cmd;
	int err = 0;

	err = pohmelfs_data_recv(st, st->data, cmd->size);
	if (err)
		return err;

	switch (cmd->id) {
		case POHMELFS_CRYPTO_CAPABILITIES:
			return pohmelfs_crypto_cap_response(st);
		case POHMELFS_ROOT_CAPABILITIES:
			return pohmelfs_root_cap_response(st);
		default:
			break;
	}
	return -EINVAL;
}