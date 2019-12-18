#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  iv ;
struct TYPE_8__ {int /*<<< orphan*/  sequence; } ;
typedef  TYPE_1__ VariantStream ;
struct TYPE_9__ {char* iv; char* key_string; char* key; int (* io_open ) (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * key_file; int /*<<< orphan*/ * key_uri; int /*<<< orphan*/ * iv_string; int /*<<< orphan*/ * key_basename; int /*<<< orphan*/ * key_url; int /*<<< orphan*/ * url; struct TYPE_9__* priv_data; } ;
typedef  TYPE_2__ HLSContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_WB64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int KEYSIZE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_mallocz (int) ; 
 int /*<<< orphan*/  av_strlcat (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  av_strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_data_to_hex (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int randomize (int /*<<< orphan*/ *,int) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_encrypt(AVFormatContext *s, VariantStream *vs)
{
    HLSContext *hls = s->priv_data;
    int ret;
    int len;
    AVIOContext *pb;
    uint8_t key[KEYSIZE];

    len = strlen(s->url) + 4 + 1;
    hls->key_basename = av_mallocz(len);
    if (!hls->key_basename)
        return AVERROR(ENOMEM);

    av_strlcpy(hls->key_basename, s->url, len);
    av_strlcat(hls->key_basename, ".key", len);

    if (hls->key_url) {
        av_strlcpy(hls->key_file, hls->key_url, sizeof(hls->key_file));
        av_strlcpy(hls->key_uri, hls->key_url, sizeof(hls->key_uri));
    } else {
        av_strlcpy(hls->key_file, hls->key_basename, sizeof(hls->key_file));
        av_strlcpy(hls->key_uri, hls->key_basename, sizeof(hls->key_uri));
    }

    if (!*hls->iv_string) {
        uint8_t iv[16] = { 0 };
        char buf[33];

        if (!hls->iv) {
            AV_WB64(iv + 8, vs->sequence);
        } else {
            memcpy(iv, hls->iv, sizeof(iv));
        }
        ff_data_to_hex(buf, iv, sizeof(iv), 0);
        buf[32] = '\0';
        memcpy(hls->iv_string, buf, sizeof(hls->iv_string));
    }

    if (!*hls->key_uri) {
        av_log(hls, AV_LOG_ERROR, "no key URI specified in key info file\n");
        return AVERROR(EINVAL);
    }

    if (!*hls->key_file) {
        av_log(hls, AV_LOG_ERROR, "no key file specified in key info file\n");
        return AVERROR(EINVAL);
    }

    if (!*hls->key_string) {
        if (!hls->key) {
            if ((ret = randomize(key, sizeof(key))) < 0) {
                av_log(s, AV_LOG_ERROR, "Cannot generate a strong random key\n");
                return ret;
            }
        } else {
            memcpy(key, hls->key, sizeof(key));
        }

        ff_data_to_hex(hls->key_string, key, sizeof(key), 0);
        if ((ret = s->io_open(s, &pb, hls->key_file, AVIO_FLAG_WRITE, NULL)) < 0)
            return ret;
        avio_seek(pb, 0, SEEK_CUR);
        avio_write(pb, key, KEYSIZE);
        avio_close(pb);
    }
    return 0;
}