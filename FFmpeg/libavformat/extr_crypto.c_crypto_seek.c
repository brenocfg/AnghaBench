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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  errbuf ;
struct TYPE_6__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_7__ {int flags; scalar_t__ position; int /*<<< orphan*/  hd; int /*<<< orphan*/  ivlen; int /*<<< orphan*/  iv; int /*<<< orphan*/  decrypt_iv; int /*<<< orphan*/  outbuffer; int /*<<< orphan*/  outptr; scalar_t__ indata_used; scalar_t__ indata; scalar_t__ outdata; scalar_t__ eof; } ;
typedef  TYPE_2__ CryptoContext ;

/* Variables and functions */
 scalar_t__ AVERROR (int /*<<< orphan*/ ) ; 
 int AVIO_FLAG_WRITE ; 
#define  AVSEEK_SIZE 131 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ BLOCKSIZE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ESPIPE ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_strerror (int,char*,int) ; 
 int crypto_read (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ffurl_seek (int /*<<< orphan*/ ,scalar_t__,int const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t crypto_seek(URLContext *h, int64_t pos, int whence)
{
    CryptoContext *c = h->priv_data;
    int64_t block;
    int64_t newpos;

    if (c->flags & AVIO_FLAG_WRITE) {
        av_log(h, AV_LOG_ERROR,
            "Crypto: seek not supported for write\r\n");
        /* seems the most appropriate error to return */
        return AVERROR(ESPIPE);
    }

    // reset eof, else we won't read it correctly if we already hit eof.
    c->eof = 0;

    switch (whence) {
    case SEEK_SET:
        break;
    case SEEK_CUR:
        pos = pos + c->position;
        break;
    case SEEK_END: {
        int64_t newpos = ffurl_seek( c->hd, pos, AVSEEK_SIZE );
        if (newpos < 0) {
            av_log(h, AV_LOG_ERROR,
                "Crypto: seek_end - can't get file size (pos=%lld)\r\n", (long long int)pos);
            return newpos;
        }
        pos = newpos - pos;
        }
        break;
    case AVSEEK_SIZE: {
        int64_t newpos = ffurl_seek( c->hd, pos, AVSEEK_SIZE );
        return newpos;
        }
        break;
    default:
        av_log(h, AV_LOG_ERROR,
            "Crypto: no support for seek where 'whence' is %d\r\n", whence);
        return AVERROR(EINVAL);
    }

    c->outdata = 0;
    c->indata = 0;
    c->indata_used = 0;
    c->outptr = c->outbuffer;

    // identify the block containing the IV for the
    // next block we will decrypt
    block = pos/BLOCKSIZE;
    if (block == 0) {
        // restore the iv to the seed one - this is the iv for the FIRST block
        memcpy( c->decrypt_iv, c->iv, c->ivlen );
        c->position = 0;
    } else {
        // else, go back one block - we will get av_cyrpt to read this block
        // which it will then store use as the iv.
        // note that the DECRYPTED result will not be correct,
        // but will be discarded
        block--;
        c->position = (block * BLOCKSIZE);
    }

    newpos = ffurl_seek( c->hd, c->position, SEEK_SET );
    if (newpos < 0) {
        av_log(h, AV_LOG_ERROR,
            "Crypto: nested protocol no support for seek or seek failed\n");
        return newpos;
    }

    // read and discard from here up to required position
    // (which will set the iv correctly to it).
    if (pos - c->position) {
        uint8_t buff[BLOCKSIZE*2]; // maximum size of pos-c->position
        int len = pos - c->position;
        int res;

        while (len > 0) {
            // note: this may not return all the bytes first time
            res = crypto_read(h, buff, len);
            if (res < 0)
                break;
            len -= res;
        }

        // if we did not get all the bytes
        if (len != 0) {
            char errbuf[100] = "unknown error";
            av_strerror(res, errbuf, sizeof(errbuf));
            av_log(h, AV_LOG_ERROR,
                "Crypto: discard read did not get all the bytes (%d remain) - read returned (%d)-%s\n",
                len, res, errbuf);
            return AVERROR(EINVAL);
        }
    }

    return c->position;
}