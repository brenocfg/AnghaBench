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
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int /*<<< orphan*/  dh; } ;
typedef  TYPE_2__ RTMPEContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int ff_dh_generate_public_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_dh_init (int) ; 
 int ff_dh_write_public_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ff_rtmp_calc_digest_pos (int /*<<< orphan*/ *,int,int,int) ; 

int ff_rtmpe_gen_pub_key(URLContext *h, uint8_t *buf)
{
    RTMPEContext *rt = h->priv_data;
    int offset, ret;

    if (!(rt->dh = ff_dh_init(1024)))
        return AVERROR(ENOMEM);

    offset = ff_rtmp_calc_digest_pos(buf, 768, 632, 8);
    if (offset < 0)
        return offset;

    /* generate a Diffie-Hellmann public key */
    if ((ret = ff_dh_generate_public_key(rt->dh)) < 0)
        return ret;

    /* write the public key into the handshake buffer */
    if ((ret = ff_dh_write_public_key(rt->dh, buf + offset, 128)) < 0)
        return ret;

    return 0;
}