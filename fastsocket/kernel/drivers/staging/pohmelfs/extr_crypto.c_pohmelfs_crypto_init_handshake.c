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
struct pohmelfs_sb {int cipher_strlen; int hash_strlen; char* hash_string; char* cipher_string; int flags; int perform_crypto; int /*<<< orphan*/  wait_on_page_timeout; int /*<<< orphan*/  wait; int /*<<< orphan*/  cipher_keysize; } ;
struct netfs_trans {struct pohmelfs_sb* private; int /*<<< orphan*/  complete; } ;
struct netfs_crypto_capabilities {int hash_strlen; int cipher_strlen; int /*<<< orphan*/  cipher_keysize; } ;
struct netfs_cmd {int size; scalar_t__ csize; scalar_t__ ext; scalar_t__ start; int /*<<< orphan*/  id; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  NETFS_CAPABILITIES ; 
 int /*<<< orphan*/  POHMELFS_CRYPTO_CAPABILITIES ; 
 int /*<<< orphan*/  netfs_convert_cmd (struct netfs_cmd*) ; 
 int /*<<< orphan*/  netfs_convert_crypto_capabilities (struct netfs_crypto_capabilities*) ; 
 struct netfs_trans* netfs_trans_alloc (struct pohmelfs_sb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netfs_cmd* netfs_trans_current (struct netfs_trans*) ; 
 int netfs_trans_finish (struct netfs_trans*,struct pohmelfs_sb*) ; 
 int /*<<< orphan*/  netfs_trans_update (struct netfs_cmd*,struct netfs_trans*,int) ; 
 int /*<<< orphan*/  pohmelfs_crypt_init_complete ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pohmelfs_crypto_init_handshake(struct pohmelfs_sb *psb)
{
	struct netfs_trans *t;
	struct netfs_crypto_capabilities *cap;
	struct netfs_cmd *cmd;
	char *str;
	int err = -ENOMEM, size;

	size = sizeof(struct netfs_crypto_capabilities) +
		psb->cipher_strlen + psb->hash_strlen + 2; /* 0 bytes */

	t = netfs_trans_alloc(psb, size, 0, 0);
	if (!t)
		goto err_out_exit;

	t->complete = pohmelfs_crypt_init_complete;
	t->private = psb;

	cmd = netfs_trans_current(t);
	cap = (struct netfs_crypto_capabilities *)(cmd + 1);
	str = (char *)(cap + 1);

	cmd->cmd = NETFS_CAPABILITIES;
	cmd->id = POHMELFS_CRYPTO_CAPABILITIES;
	cmd->size = size;
	cmd->start = 0;
	cmd->ext = 0;
	cmd->csize = 0;

	netfs_convert_cmd(cmd);
	netfs_trans_update(cmd, t, size);

	cap->hash_strlen = psb->hash_strlen;
	if (cap->hash_strlen) {
		sprintf(str, "%s", psb->hash_string);
		str += cap->hash_strlen;
	}

	cap->cipher_strlen = psb->cipher_strlen;
	cap->cipher_keysize = psb->cipher_keysize;
	if (cap->cipher_strlen)
		sprintf(str, "%s", psb->cipher_string);

	netfs_convert_crypto_capabilities(cap);

	psb->flags = ~0;
	err = netfs_trans_finish(t, psb);
	if (err)
		goto err_out_exit;

	err = wait_event_interruptible_timeout(psb->wait, (psb->flags != ~0),
			psb->wait_on_page_timeout);
	if (!err)
		err = -ETIMEDOUT;
	else if (err > 0)
		err = -psb->flags;

	if (!err)
		psb->perform_crypto = 1;
	psb->flags = 0;

	/*
	 * At this point NETFS_CAPABILITIES response command
	 * should setup superblock in a way, which is acceptible
	 * for both client and server, so if server refuses connection,
	 * it will send error in transaction response.
	 */

	if (err)
		goto err_out_exit;

	return 0;

err_out_exit:
	return err;
}