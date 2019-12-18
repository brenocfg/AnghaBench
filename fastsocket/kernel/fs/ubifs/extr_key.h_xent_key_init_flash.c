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
union ubifs_key {void** j32; } ;
typedef  int uint32_t ;
struct ubifs_info {int (* key_hash ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
typedef  int ino_t ;

/* Variables and functions */
 scalar_t__ UBIFS_MAX_KEY_LEN ; 
 int UBIFS_S_KEY_HASH_BITS ; 
 int UBIFS_S_KEY_HASH_MASK ; 
 int UBIFS_XENT_KEY ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 

__attribute__((used)) static inline void xent_key_init_flash(const struct ubifs_info *c, void *k,
				       ino_t inum, const struct qstr *nm)
{
	union ubifs_key *key = k;
	uint32_t hash = c->key_hash(nm->name, nm->len);

	ubifs_assert(!(hash & ~UBIFS_S_KEY_HASH_MASK));
	key->j32[0] = cpu_to_le32(inum);
	key->j32[1] = cpu_to_le32(hash |
				  (UBIFS_XENT_KEY << UBIFS_S_KEY_HASH_BITS));
	memset(k + 8, 0, UBIFS_MAX_KEY_LEN - 8);
}