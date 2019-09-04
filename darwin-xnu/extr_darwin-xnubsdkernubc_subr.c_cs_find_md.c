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
typedef  scalar_t__ uint8_t ;
struct cs_hash {int dummy; } ;

/* Variables and functions */
 scalar_t__ CS_HASHTYPE_SHA1 ; 
 struct cs_hash const cs_hash_sha1 ; 

__attribute__((used)) static struct cs_hash const *
cs_find_md(uint8_t type)
{
	if (type == CS_HASHTYPE_SHA1) {
		return &cs_hash_sha1;
#if CRYPTO_SHA2
	} else if (type == CS_HASHTYPE_SHA256) {
		return &cs_hash_sha256;
	} else if (type == CS_HASHTYPE_SHA256_TRUNCATED) {
		return &cs_hash_sha256_truncate;
	} else if (type == CS_HASHTYPE_SHA384) {
		return &cs_hash_sha384;
#endif
	}
	return NULL;
}