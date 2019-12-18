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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int handshaked; int /*<<< orphan*/  key_out; int /*<<< orphan*/  key_in; } ;
typedef  TYPE_2__ RTMPEContext ;

/* Variables and functions */
 int RTMP_HANDSHAKE_PACKET_SIZE ; 
 int /*<<< orphan*/  av_rc4_crypt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

int ff_rtmpe_update_keystream(URLContext *h)
{
    RTMPEContext *rt = h->priv_data;
    char buf[RTMP_HANDSHAKE_PACKET_SIZE];

    /* skip past 1536 bytes of the RC4 bytestream */
    av_rc4_crypt(&rt->key_in, buf, NULL, sizeof(buf), NULL, 1);
    av_rc4_crypt(&rt->key_out, buf, NULL, sizeof(buf), NULL, 1);

    /* the next requests will be encrypted using RC4 keys */
    rt->handshaked = 1;

    return 0;
}