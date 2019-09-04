#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int is_streamed; TYPE_3__* priv_data; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_10__ {int n_segments; int n_variants; scalar_t__ start_seq_no; scalar_t__ cur_seq_no; int /*<<< orphan*/  finished; int /*<<< orphan*/  playlisturl; TYPE_1__** variants; } ;
struct TYPE_8__ {int bandwidth; char const* url; } ;
typedef  TYPE_3__ HLSContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ av_strstart (char const*,char*,char const**) ; 
 int /*<<< orphan*/  hls_close (TYPE_2__*) ; 
 int parse_playlist (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hls_open(URLContext *h, const char *uri, int flags)
{
    HLSContext *s = h->priv_data;
    int ret, i;
    const char *nested_url;

    if (flags & AVIO_FLAG_WRITE)
        return AVERROR(ENOSYS);

    h->is_streamed = 1;

    if (av_strstart(uri, "hls+", &nested_url)) {
        av_strlcpy(s->playlisturl, nested_url, sizeof(s->playlisturl));
    } else if (av_strstart(uri, "hls://", &nested_url)) {
        av_log(h, AV_LOG_ERROR,
               "No nested protocol specified. Specify e.g. hls+http://%s\n",
               nested_url);
        ret = AVERROR(EINVAL);
        goto fail;
    } else {
        av_log(h, AV_LOG_ERROR, "Unsupported url %s\n", uri);
        ret = AVERROR(EINVAL);
        goto fail;
    }
    av_log(h, AV_LOG_WARNING,
           "Using the hls protocol is discouraged, please try using the "
           "hls demuxer instead. The hls demuxer should be more complete "
           "and work as well as the protocol implementation. (If not, "
           "please report it.) To use the demuxer, simply use %s as url.\n",
           s->playlisturl);

    if ((ret = parse_playlist(h, s->playlisturl)) < 0)
        goto fail;

    if (s->n_segments == 0 && s->n_variants > 0) {
        int max_bandwidth = 0, maxvar = -1;
        for (i = 0; i < s->n_variants; i++) {
            if (s->variants[i]->bandwidth > max_bandwidth || i == 0) {
                max_bandwidth = s->variants[i]->bandwidth;
                maxvar = i;
            }
        }
        av_strlcpy(s->playlisturl, s->variants[maxvar]->url,
                   sizeof(s->playlisturl));
        if ((ret = parse_playlist(h, s->playlisturl)) < 0)
            goto fail;
    }

    if (s->n_segments == 0) {
        av_log(h, AV_LOG_WARNING, "Empty playlist\n");
        ret = AVERROR(EIO);
        goto fail;
    }
    s->cur_seq_no = s->start_seq_no;
    if (!s->finished && s->n_segments >= 3)
        s->cur_seq_no = s->start_seq_no + s->n_segments - 3;

    return 0;

fail:
    hls_close(h);
    return ret;
}