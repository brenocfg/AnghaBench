#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* hmac_update ;
typedef  int /*<<< orphan*/  hmac_init ;
typedef  void* hmac_final ;
typedef  enum AVHMACType { ____Placeholder_AVHMACType } AVHMACType ;
struct TYPE_5__ {int blocklen; int hashlen; void* hash; void* final; void* update; int /*<<< orphan*/  init; } ;
typedef  TYPE_1__ AVHMAC ;

/* Variables and functions */
#define  AV_HMAC_MD5 133 
#define  AV_HMAC_SHA1 132 
#define  AV_HMAC_SHA224 131 
#define  AV_HMAC_SHA256 130 
#define  AV_HMAC_SHA384 129 
#define  AV_HMAC_SHA512 128 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 TYPE_1__* av_mallocz (int) ; 
 void* av_md5_alloc () ; 
 int /*<<< orphan*/  av_md5_final ; 
 int /*<<< orphan*/  av_md5_init ; 
 int /*<<< orphan*/  av_md5_update ; 
 void* av_sha512_alloc () ; 
 int /*<<< orphan*/  av_sha512_final ; 
 int /*<<< orphan*/  av_sha512_update ; 
 void* av_sha_alloc () ; 
 int /*<<< orphan*/  av_sha_final ; 
 int /*<<< orphan*/  av_sha_update ; 
 int /*<<< orphan*/  sha160_init ; 
 int /*<<< orphan*/  sha224_init ; 
 int /*<<< orphan*/  sha256_init ; 
 int /*<<< orphan*/  sha384_init ; 
 int /*<<< orphan*/  sha512_init ; 

AVHMAC *av_hmac_alloc(enum AVHMACType type)
{
    AVHMAC *c = av_mallocz(sizeof(*c));
    if (!c)
        return NULL;
    switch (type) {
    case AV_HMAC_MD5:
        c->blocklen = 64;
        c->hashlen  = 16;
        c->init     = (hmac_init) av_md5_init;
        c->update   = (hmac_update) av_md5_update;
        c->final    = (hmac_final) av_md5_final;
        c->hash     = av_md5_alloc();
        break;
    case AV_HMAC_SHA1:
        c->blocklen = 64;
        c->hashlen  = 20;
        c->init     = sha160_init;
        c->update   = (hmac_update) av_sha_update;
        c->final    = (hmac_final) av_sha_final;
        c->hash     = av_sha_alloc();
        break;
    case AV_HMAC_SHA224:
        c->blocklen = 64;
        c->hashlen  = 28;
        c->init     = sha224_init;
        c->update   = (hmac_update) av_sha_update;
        c->final    = (hmac_final) av_sha_final;
        c->hash     = av_sha_alloc();
        break;
    case AV_HMAC_SHA256:
        c->blocklen = 64;
        c->hashlen  = 32;
        c->init     = sha256_init;
        c->update   = (hmac_update) av_sha_update;
        c->final    = (hmac_final) av_sha_final;
        c->hash     = av_sha_alloc();
        break;
    case AV_HMAC_SHA384:
        c->blocklen = 128;
        c->hashlen  = 48;
        c->init     = sha384_init;
        c->update   = (hmac_update) av_sha512_update;
        c->final    = (hmac_final) av_sha512_final;
        c->hash     = av_sha512_alloc();
        break;
    case AV_HMAC_SHA512:
        c->blocklen = 128;
        c->hashlen  = 64;
        c->init     = sha512_init;
        c->update   = (hmac_update) av_sha512_update;
        c->final    = (hmac_final) av_sha512_final;
        c->hash     = av_sha512_alloc();
        break;
    default:
        av_free(c);
        return NULL;
    }
    if (!c->hash) {
        av_free(c);
        return NULL;
    }
    return c;
}