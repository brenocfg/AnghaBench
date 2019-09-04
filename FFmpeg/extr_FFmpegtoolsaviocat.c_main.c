#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {int error; } ;
typedef  TYPE_1__ AVIOContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int AV_TIME_BASE ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 scalar_t__ av_dict_parse_string (int /*<<< orphan*/ **,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int av_gettime_relative () ; 
 int /*<<< orphan*/  av_strerror (int,char*,int) ; 
 int /*<<< orphan*/  av_usleep (int) ; 
 int /*<<< orphan*/  avformat_network_deinit () ; 
 int /*<<< orphan*/  avformat_network_init () ; 
 int /*<<< orphan*/  avio_close (TYPE_1__*) ; 
 int /*<<< orphan*/  avio_flush (TYPE_1__*) ; 
 int avio_open2 (TYPE_1__**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int avio_read (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int avio_size (TYPE_1__*) ; 
 int /*<<< orphan*/  avio_write (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int usage (char*,int) ; 

int main(int argc, char **argv)
{
    int bps = 0, duration = 0, ret, i;
    const char *input_url = NULL, *output_url = NULL;
    int64_t stream_pos = 0;
    int64_t start_time;
    char errbuf[50];
    AVIOContext *input, *output;
    AVDictionary *in_opts = NULL;
    AVDictionary *out_opts = NULL;

    avformat_network_init();

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-b") && i + 1 < argc) {
            bps = atoi(argv[i + 1]);
            i++;
        } else if (!strcmp(argv[i], "-d") && i + 1 < argc) {
            duration = atoi(argv[i + 1]);
            i++;
        } else if (!strcmp(argv[i], "-oi") && i + 1 < argc) {
            if (av_dict_parse_string(&in_opts, argv[i + 1], "=", ":", 0) < 0) {
                fprintf(stderr, "Cannot parse option string %s\n",
                        argv[i + 1]);
                return usage(argv[0], 1);
            }
            i++;
        } else if (!strcmp(argv[i], "-oo") && i + 1 < argc) {
            if (av_dict_parse_string(&out_opts, argv[i + 1], "=", ":", 0) < 0) {
                fprintf(stderr, "Cannot parse option string %s\n",
                        argv[i + 1]);
                return usage(argv[0], 1);
            }
            i++;
        } else if (!input_url) {
            input_url = argv[i];
        } else if (!output_url) {
            output_url = argv[i];
        } else {
            return usage(argv[0], 1);
        }
    }
    if (!output_url)
        return usage(argv[0], 1);

    ret = avio_open2(&input, input_url, AVIO_FLAG_READ, NULL, &in_opts);
    if (ret) {
        av_strerror(ret, errbuf, sizeof(errbuf));
        fprintf(stderr, "Unable to open %s: %s\n", input_url, errbuf);
        return 1;
    }
    if (duration && !bps) {
        int64_t size = avio_size(input);
        if (size < 0) {
            av_strerror(ret, errbuf, sizeof(errbuf));
            fprintf(stderr, "Unable to get size of %s: %s\n", input_url, errbuf);
            goto fail;
        }
        bps = size / duration;
    }
    ret = avio_open2(&output, output_url, AVIO_FLAG_WRITE, NULL, &out_opts);
    if (ret) {
        av_strerror(ret, errbuf, sizeof(errbuf));
        fprintf(stderr, "Unable to open %s: %s\n", output_url, errbuf);
        goto fail;
    }

    start_time = av_gettime_relative();
    while (1) {
        uint8_t buf[1024];
        int n;
        n = avio_read(input, buf, sizeof(buf));
        if (n <= 0)
            break;
        avio_write(output, buf, n);
        if (output->error) {
            av_strerror(output->error, errbuf, sizeof(errbuf));
            fprintf(stderr, "Unable to write %s: %s\n", output_url, errbuf);
            break;
        }
        stream_pos += n;
        if (bps) {
            avio_flush(output);
            while ((av_gettime_relative() - start_time) * bps / AV_TIME_BASE < stream_pos)
                av_usleep(50 * 1000);
        }
    }

    avio_flush(output);
    avio_close(output);

fail:
    av_dict_free(&in_opts);
    av_dict_free(&out_opts);
    avio_close(input);
    avformat_network_deinit();
    return ret ? 1 : 0;
}