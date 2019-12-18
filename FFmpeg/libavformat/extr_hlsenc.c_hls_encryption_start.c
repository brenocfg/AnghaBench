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
struct TYPE_9__ {int (* io_open ) (TYPE_2__*,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_1__* priv_data; } ;
struct TYPE_8__ {char* key_info_file; char* key_uri; char* key_file; char* iv_string; int /*<<< orphan*/  key_string; } ;
typedef  TYPE_1__ HLSContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int KEYSIZE ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_data_to_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_format_io_close (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_get_line (int /*<<< orphan*/ *,char*,int) ; 
 size_t strcspn (char*,char*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hls_encryption_start(AVFormatContext *s)
{
    HLSContext *hls = s->priv_data;
    int ret;
    AVIOContext *pb;
    uint8_t key[KEYSIZE];

    if ((ret = s->io_open(s, &pb, hls->key_info_file, AVIO_FLAG_READ, NULL)) < 0) {
        av_log(hls, AV_LOG_ERROR,
               "error opening key info file %s\n", hls->key_info_file);
        return ret;
    }

    ff_get_line(pb, hls->key_uri, sizeof(hls->key_uri));
    hls->key_uri[strcspn(hls->key_uri, "\r\n")] = '\0';

    ff_get_line(pb, hls->key_file, sizeof(hls->key_file));
    hls->key_file[strcspn(hls->key_file, "\r\n")] = '\0';

    ff_get_line(pb, hls->iv_string, sizeof(hls->iv_string));
    hls->iv_string[strcspn(hls->iv_string, "\r\n")] = '\0';

    ff_format_io_close(s, &pb);

    if (!*hls->key_uri) {
        av_log(hls, AV_LOG_ERROR, "no key URI specified in key info file\n");
        return AVERROR(EINVAL);
    }

    if (!*hls->key_file) {
        av_log(hls, AV_LOG_ERROR, "no key file specified in key info file\n");
        return AVERROR(EINVAL);
    }

    if ((ret = s->io_open(s, &pb, hls->key_file, AVIO_FLAG_READ, NULL)) < 0) {
        av_log(hls, AV_LOG_ERROR, "error opening key file %s\n", hls->key_file);
        return ret;
    }

    ret = avio_read(pb, key, sizeof(key));
    ff_format_io_close(s, &pb);
    if (ret != sizeof(key)) {
        av_log(hls, AV_LOG_ERROR, "error reading key file %s\n", hls->key_file);
        if (ret >= 0 || ret == AVERROR_EOF)
            ret = AVERROR(EINVAL);
        return ret;
    }
    ff_data_to_hex(hls->key_string, key, sizeof(key), 0);

    return 0;
}