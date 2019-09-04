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
struct TYPE_3__ {unsigned int hashlen; int keylen; int* key; int blocklen; int /*<<< orphan*/  hash; int /*<<< orphan*/  (* final ) (int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ ,int*,unsigned int) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ AVHMAC ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int MAX_BLOCKLEN ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int*,unsigned int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int*) ; 

int av_hmac_final(AVHMAC *c, uint8_t *out, unsigned int outlen)
{
    uint8_t block[MAX_BLOCKLEN];
    int i;
    if (outlen < c->hashlen)
        return AVERROR(EINVAL);
    c->final(c->hash, out);
    c->init(c->hash);
    for (i = 0; i < c->keylen; i++)
        block[i] = c->key[i] ^ 0x5C;
    for (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x5C;
    c->update(c->hash, block, c->blocklen);
    c->update(c->hash, out, c->hashlen);
    c->final(c->hash, out);
    return c->hashlen;
}