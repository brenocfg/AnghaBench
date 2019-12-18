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
struct ecryptfs_crypt_stat {int /*<<< orphan*/  key_size; int /*<<< orphan*/  key; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECRYPTFS_KEY_VALID ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  ecryptfs_compute_root_iv (struct ecryptfs_crypt_stat*) ; 
 int /*<<< orphan*/  ecryptfs_dump_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecryptfs_printk (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ecryptfs_verbosity ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ecryptfs_generate_new_key(struct ecryptfs_crypt_stat *crypt_stat)
{
	get_random_bytes(crypt_stat->key, crypt_stat->key_size);
	crypt_stat->flags |= ECRYPTFS_KEY_VALID;
	ecryptfs_compute_root_iv(crypt_stat);
	if (unlikely(ecryptfs_verbosity > 0)) {
		ecryptfs_printk(KERN_DEBUG, "Generated new session key:\n");
		ecryptfs_dump_hex(crypt_stat->key,
				  crypt_stat->key_size);
	}
}