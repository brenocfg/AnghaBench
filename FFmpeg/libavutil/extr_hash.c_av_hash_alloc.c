#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int type; int /*<<< orphan*/  ctx; int /*<<< orphan*/  crctab; } ;
typedef  TYPE_1__ AVHashContext ;

/* Variables and functions */
#define  ADLER32 142 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_CRC_32_IEEE_LE ; 
#define  CRC32 141 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
#define  MD5 140 
#define  MURMUR3 139 
 int NUM_HASHES ; 
#define  RIPEMD128 138 
#define  RIPEMD160 137 
#define  RIPEMD256 136 
#define  RIPEMD320 135 
#define  SHA160 134 
#define  SHA224 133 
#define  SHA256 132 
#define  SHA384 131 
#define  SHA512 130 
#define  SHA512_224 129 
#define  SHA512_256 128 
 int /*<<< orphan*/  av_crc_get_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 TYPE_1__* av_mallocz (int) ; 
 int /*<<< orphan*/  av_md5_alloc () ; 
 int /*<<< orphan*/  av_murmur3_alloc () ; 
 int /*<<< orphan*/  av_ripemd_alloc () ; 
 int /*<<< orphan*/  av_sha512_alloc () ; 
 int /*<<< orphan*/  av_sha_alloc () ; 
 scalar_t__ av_strcasecmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* hashdesc ; 

int av_hash_alloc(AVHashContext **ctx, const char *name)
{
    AVHashContext *res;
    int i;
    *ctx = NULL;
    for (i = 0; i < NUM_HASHES; i++)
        if (av_strcasecmp(name, hashdesc[i].name) == 0)
            break;
    if (i >= NUM_HASHES) return AVERROR(EINVAL);
    res = av_mallocz(sizeof(*res));
    if (!res) return AVERROR(ENOMEM);
    res->type = i;
    switch (i) {
    case MD5:     res->ctx = av_md5_alloc(); break;
    case MURMUR3: res->ctx = av_murmur3_alloc(); break;
    case RIPEMD128:
    case RIPEMD160:
    case RIPEMD256:
    case RIPEMD320: res->ctx = av_ripemd_alloc(); break;
    case SHA160:
    case SHA224:
    case SHA256:  res->ctx = av_sha_alloc(); break;
    case SHA512_224:
    case SHA512_256:
    case SHA384:
    case SHA512:  res->ctx = av_sha512_alloc(); break;
    case CRC32:   res->crctab = av_crc_get_table(AV_CRC_32_IEEE_LE); break;
    case ADLER32: break;
    }
    if (i != ADLER32 && i != CRC32 && !res->ctx) {
        av_free(res);
        return AVERROR(ENOMEM);
    }
    *ctx = res;
    return 0;
}