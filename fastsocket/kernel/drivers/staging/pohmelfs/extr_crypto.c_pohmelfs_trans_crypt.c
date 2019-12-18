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
struct pohmelfs_sb {int /*<<< orphan*/  perform_crypto; int /*<<< orphan*/  cipher_string; int /*<<< orphan*/  hash_string; } ;
struct netfs_trans {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netfs_trans_get (struct netfs_trans*) ; 
 int pohmelfs_crypto_finish (struct netfs_trans*,struct pohmelfs_sb*,int /*<<< orphan*/ ) ; 
 int pohmelfs_crypto_thread_get (struct pohmelfs_sb*,int /*<<< orphan*/ ,struct netfs_trans*) ; 
 int /*<<< orphan*/  pohmelfs_trans_crypt_action ; 

int pohmelfs_trans_crypt(struct netfs_trans *trans, struct pohmelfs_sb *psb)
{
	if ((!psb->hash_string && !psb->cipher_string) || !psb->perform_crypto) {
		netfs_trans_get(trans);
		return pohmelfs_crypto_finish(trans, psb, 0);
	}

	return pohmelfs_crypto_thread_get(psb, pohmelfs_trans_crypt_action, trans);
}