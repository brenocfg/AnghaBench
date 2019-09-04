#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct AVDES {int dummy; } ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {unsigned int k_size; unsigned int e_size; unsigned int i_size; int /*<<< orphan*/  sm_val; int /*<<< orphan*/  const* s_val; int /*<<< orphan*/  const* m_val; } ;
typedef  TYPE_1__ OMAContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 unsigned int OMA_ENC_HEADER_SIZE ; 
 unsigned int OMA_RPROBE_M_VAL ; 
 struct AVDES* av_des_alloc () ; 
 int /*<<< orphan*/  av_des_crypt (struct AVDES*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_des_init (struct AVDES*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  av_des_mac (struct AVDES*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_free (struct AVDES*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rprobe(AVFormatContext *s, uint8_t *enc_header, unsigned size,
                  const uint8_t *r_val)
{
    OMAContext *oc = s->priv_data;
    unsigned int pos;
    struct AVDES *av_des;

    if (!enc_header || !r_val ||
        size < OMA_ENC_HEADER_SIZE + oc->k_size + oc->e_size + oc->i_size ||
        size < OMA_RPROBE_M_VAL)
        return -1;

    av_des = av_des_alloc();
    if (!av_des)
        return AVERROR(ENOMEM);

    /* m_val */
    av_des_init(av_des, r_val, 192, 1);
    av_des_crypt(av_des, oc->m_val, &enc_header[48], 1, NULL, 1);

    /* s_val */
    av_des_init(av_des, oc->m_val, 64, 0);
    av_des_crypt(av_des, oc->s_val, NULL, 1, NULL, 0);

    /* sm_val */
    pos = OMA_ENC_HEADER_SIZE + oc->k_size + oc->e_size;
    av_des_init(av_des, oc->s_val, 64, 0);
    av_des_mac(av_des, oc->sm_val, &enc_header[pos], (oc->i_size >> 3));

    pos += oc->i_size;

    av_free(av_des);

    return memcmp(&enc_header[pos], oc->sm_val, 8) ? -1 : 0;
}