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
typedef  int /*<<< orphan*/  uint8_t ;
struct sadb_msghdr {int* extlen; int /*<<< orphan*/ ** ext; } ;
struct sadb_key {int sadb_key_bits; } ;

/* Variables and functions */
 size_t SADB_EXT_KEY_AUTH ; 
 size_t SADB_EXT_KEY_ENCRYPT ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
bzero_keys(const struct sadb_msghdr *mh)
{
	int extlen = 0;
	int offset = 0;

	if (!mh) {
		return;
	}
	offset = sizeof(struct sadb_key);

	if (mh->ext[SADB_EXT_KEY_ENCRYPT]) {
		struct sadb_key *key = (struct sadb_key*)mh->ext[SADB_EXT_KEY_ENCRYPT];
		extlen = key->sadb_key_bits >> 3;

		if (mh->extlen[SADB_EXT_KEY_ENCRYPT] >= offset + extlen) {
			bzero((uint8_t *)mh->ext[SADB_EXT_KEY_ENCRYPT]+offset, extlen);
		} else {
			bzero(mh->ext[SADB_EXT_KEY_ENCRYPT], mh->extlen[SADB_EXT_KEY_ENCRYPT]);
		}
	}
	if (mh->ext[SADB_EXT_KEY_AUTH]) {
		struct sadb_key *key = (struct sadb_key*)mh->ext[SADB_EXT_KEY_AUTH];
		extlen = key->sadb_key_bits >> 3;

		if (mh->extlen[SADB_EXT_KEY_AUTH] >= offset + extlen) {
			bzero((uint8_t *)mh->ext[SADB_EXT_KEY_AUTH]+offset, extlen);
		} else {
			bzero(mh->ext[SADB_EXT_KEY_AUTH], mh->extlen[SADB_EXT_KEY_AUTH]);
		}
	}
}