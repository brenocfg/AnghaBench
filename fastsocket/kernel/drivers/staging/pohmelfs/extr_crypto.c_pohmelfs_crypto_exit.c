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
struct pohmelfs_sb {int /*<<< orphan*/  cipher_string; int /*<<< orphan*/  hash_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pohmelfs_sys_crypto_exit (struct pohmelfs_sb*) ; 

void pohmelfs_crypto_exit(struct pohmelfs_sb *psb)
{
	pohmelfs_sys_crypto_exit(psb);

	kfree(psb->hash_string);
	kfree(psb->cipher_string);
}