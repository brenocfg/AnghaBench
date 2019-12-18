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
struct svc_expkey {int ek_fsidtype; int /*<<< orphan*/  ek_client; scalar_t__ ek_fsid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPKEY_HASHBITS ; 
 int EXPKEY_HASHMASK ; 
 int hash_mem (char*,int,int /*<<< orphan*/ ) ; 
 int hash_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int key_len (int) ; 

__attribute__((used)) static int
svc_expkey_hash(struct svc_expkey *item)
{
	int hash = item->ek_fsidtype;
	char * cp = (char*)item->ek_fsid;
	int len = key_len(item->ek_fsidtype);

	hash ^= hash_mem(cp, len, EXPKEY_HASHBITS);
	hash ^= hash_ptr(item->ek_client, EXPKEY_HASHBITS);
	hash &= EXPKEY_HASHMASK;
	return hash;
}