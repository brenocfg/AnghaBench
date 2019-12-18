#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint64_t ;
typedef  int uint32_t ;
struct AVDES {int dummy; } ;
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {unsigned int k_size; int rid; int /*<<< orphan*/  r_val; } ;
typedef  TYPE_1__ OMAContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int AV_RB32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENOMEM ; 
 unsigned int OMA_ENC_HEADER_SIZE ; 
 struct AVDES* av_des_alloc () ; 
 int /*<<< orphan*/  av_des_crypt (struct AVDES*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_des_init (struct AVDES*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  av_free (struct AVDES*) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kset (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  rprobe (TYPE_2__*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nprobe(AVFormatContext *s, uint8_t *enc_header, unsigned size,
                  const uint8_t *n_val)
{
    OMAContext *oc = s->priv_data;
    uint64_t pos;
    uint32_t taglen, datalen;
    struct AVDES *av_des;

    if (!enc_header || !n_val ||
        size < OMA_ENC_HEADER_SIZE + oc->k_size + 4)
        return -1;

    pos = OMA_ENC_HEADER_SIZE + oc->k_size;
    if (!memcmp(&enc_header[pos], "EKB ", 4))
        pos += 32;

    if (size < pos + 44)
        return -1;

    if (AV_RB32(&enc_header[pos]) != oc->rid)
        av_log(s, AV_LOG_DEBUG, "Mismatching RID\n");

    taglen  = AV_RB32(&enc_header[pos + 32]);
    datalen = AV_RB32(&enc_header[pos + 36]) >> 4;

    pos += 44LL + taglen;

    if (pos + (((uint64_t)datalen) << 4) > size)
        return -1;

    av_des = av_des_alloc();
    if (!av_des)
        return AVERROR(ENOMEM);

    av_des_init(av_des, n_val, 192, 1);
    while (datalen-- > 0) {
        av_des_crypt(av_des, oc->r_val, &enc_header[pos], 2, NULL, 1);
        kset(s, oc->r_val, NULL, 16);
        if (!rprobe(s, enc_header, size, oc->r_val)) {
            av_free(av_des);
            return 0;
        }
        pos += 16;
    }

    av_free(av_des);
    return -1;
}