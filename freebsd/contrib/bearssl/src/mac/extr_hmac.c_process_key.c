#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* state ) (TYPE_1__ const**,void*) ;int /*<<< orphan*/  (* update ) (TYPE_1__ const**,unsigned char*,size_t) ;int /*<<< orphan*/  (* init ) (TYPE_1__ const**) ;} ;
typedef  TYPE_1__ br_hash_class ;

/* Variables and functions */
 size_t block_size (TYPE_1__ const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,unsigned int,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__ const**) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__ const**,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__ const**,void*) ; 

__attribute__((used)) static void
process_key(const br_hash_class **hc, void *ks,
	const void *key, size_t key_len, unsigned bb)
{
	unsigned char tmp[256];
	size_t blen, u;

	blen = block_size(*hc);
	memcpy(tmp, key, key_len);
	for (u = 0; u < key_len; u ++) {
		tmp[u] ^= (unsigned char)bb;
	}
	memset(tmp + key_len, bb, blen - key_len);
	(*hc)->init(hc);
	(*hc)->update(hc, tmp, blen);
	(*hc)->state(hc, ks);
}