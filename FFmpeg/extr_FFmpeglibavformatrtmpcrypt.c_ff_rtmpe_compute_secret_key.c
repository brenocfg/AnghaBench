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
typedef  int /*<<< orphan*/  secret_key ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int /*<<< orphan*/  key_in; int /*<<< orphan*/  key_out; int /*<<< orphan*/  dh; } ;
typedef  TYPE_2__ RTMPEContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_rc4_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int ff_dh_compute_shared_secret_key (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int) ; 
 int ff_rtmp_calc_digest (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int ff_rtmp_calc_digest_pos (int /*<<< orphan*/  const*,int,int,int) ; 

int ff_rtmpe_compute_secret_key(URLContext *h, const uint8_t *serverdata,
                                const uint8_t *clientdata, int type)
{
    RTMPEContext *rt = h->priv_data;
    uint8_t secret_key[128], digest[32];
    int server_pos, client_pos;
    int ret;

    if (type) {
        if ((server_pos = ff_rtmp_calc_digest_pos(serverdata, 1532, 632, 772)) < 0)
            return server_pos;
    } else {
        if ((server_pos = ff_rtmp_calc_digest_pos(serverdata, 768, 632, 8)) < 0)
            return server_pos;
    }

    if ((client_pos = ff_rtmp_calc_digest_pos(clientdata, 768, 632, 8)) < 0)
        return client_pos;

    /* compute the shared secret secret in order to compute RC4 keys */
    if ((ret = ff_dh_compute_shared_secret_key(rt->dh, serverdata + server_pos,
                                               128, secret_key, sizeof(secret_key))) < 0)
        return ret;

    /* set output key */
    if ((ret = ff_rtmp_calc_digest(serverdata + server_pos, 128, 0, secret_key,
                                   128, digest)) < 0)
        return ret;
    av_rc4_init(&rt->key_out, digest, 16 * 8, 1);

    /* set input key */
    if ((ret = ff_rtmp_calc_digest(clientdata + client_pos, 128, 0, secret_key,
                                   128, digest)) < 0)
        return ret;
    av_rc4_init(&rt->key_in, digest, 16 * 8, 1);

    return 0;
}