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
struct pohmelfs_sb {int /*<<< orphan*/  hash_string; int /*<<< orphan*/  cipher_string; } ;

/* Variables and functions */
 int pohmelfs_crypto_init_handshake (struct pohmelfs_sb*) ; 
 int pohmelfs_sys_crypto_init (struct pohmelfs_sb*) ; 

int pohmelfs_crypto_init(struct pohmelfs_sb *psb)
{
	int err;

	if (!psb->cipher_string && !psb->hash_string)
		return 0;

	err = pohmelfs_crypto_init_handshake(psb);
	if (err)
		return err;

	err = pohmelfs_sys_crypto_init(psb);
	if (err)
		return err;

	return 0;
}