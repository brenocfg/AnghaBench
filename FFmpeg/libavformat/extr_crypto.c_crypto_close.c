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
struct TYPE_5__ {size_t pad_len; scalar_t__ write_buf; scalar_t__ aes_encrypt; scalar_t__ aes_decrypt; scalar_t__ hd; int /*<<< orphan*/  encrypt_iv; int /*<<< orphan*/ * pad; } ;
typedef  TYPE_2__ CryptoContext ;

/* Variables and functions */
 int BLOCKSIZE ; 
 int /*<<< orphan*/  av_aes_crypt (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (scalar_t__*) ; 
 int /*<<< orphan*/  ffurl_close (scalar_t__) ; 
 int ffurl_write (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int crypto_close(URLContext *h)
{
    CryptoContext *c = h->priv_data;
    int ret = 0;

    if (c->aes_encrypt) {
        uint8_t out_buf[BLOCKSIZE];
        int pad = BLOCKSIZE - c->pad_len;

        memset(&c->pad[c->pad_len], pad, pad);
        av_aes_crypt(c->aes_encrypt, out_buf, c->pad, 1, c->encrypt_iv, 0);
        ret = ffurl_write(c->hd, out_buf, BLOCKSIZE);
    }

    if (c->hd)
        ffurl_close(c->hd);
    av_freep(&c->aes_decrypt);
    av_freep(&c->aes_encrypt);
    av_freep(&c->write_buf);
    return ret;
}