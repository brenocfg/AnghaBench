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
struct TYPE_5__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  key_out; scalar_t__ handshaked; } ;
typedef  TYPE_2__ RTMPEContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_rc4_crypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int) ; 
 int ffurl_write (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int rtmpe_write(URLContext *h, const uint8_t *buf, int size)
{
    RTMPEContext *rt = h->priv_data;
    int ret;

    if (rt->handshaked) {
        /* encrypt data to send to the server */
        av_rc4_crypt(&rt->key_out, (uint8_t *)buf, buf, size, NULL, 1);
    }

    if ((ret = ffurl_write(rt->stream, buf, size)) < 0)
        return ret;

    return size;
}