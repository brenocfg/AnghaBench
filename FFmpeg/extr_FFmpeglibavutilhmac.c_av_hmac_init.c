#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {unsigned int blocklen; int* key; unsigned int keylen; unsigned int hashlen; int /*<<< orphan*/  hash; int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ ,int*,int) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* final ) (int /*<<< orphan*/ ,int*) ;} ;
typedef  TYPE_1__ AVHMAC ;

/* Variables and functions */
 int MAX_BLOCKLEN ; 
 int /*<<< orphan*/  memcpy (int*,int const*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int const*,unsigned int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int*,int) ; 

void av_hmac_init(AVHMAC *c, const uint8_t *key, unsigned int keylen)
{
    int i;
    uint8_t block[MAX_BLOCKLEN];
    if (keylen > c->blocklen) {
        c->init(c->hash);
        c->update(c->hash, key, keylen);
        c->final(c->hash, c->key);
        c->keylen = c->hashlen;
    } else {
        memcpy(c->key, key, keylen);
        c->keylen = keylen;
    }
    c->init(c->hash);
    for (i = 0; i < c->keylen; i++)
        block[i] = c->key[i] ^ 0x36;
    for (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x36;
    c->update(c->hash, block, c->blocklen);
}