#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct variant_info {char const* bandwidth; TYPE_1__ member_0; } ;
struct variant {int duration; int bandwidth; int /*<<< orphan*/  url; } ;
struct segment {int duration; int bandwidth; int /*<<< orphan*/  url; } ;
typedef  int /*<<< orphan*/  line ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  ff_parse_key_val_cb ;
struct TYPE_7__ {int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; TYPE_3__* priv_data; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_8__ {int finished; int target_duration; int start_seq_no; int /*<<< orphan*/  last_load_time; int /*<<< orphan*/  n_variants; int /*<<< orphan*/  variants; int /*<<< orphan*/  n_segments; int /*<<< orphan*/  segments; } ;
typedef  TYPE_3__ HLSContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
 int AV_TIME_BASE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int atof (char const*) ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  av_gettime_relative () ; 
 struct variant* av_malloc (int) ; 
 scalar_t__ av_strstart (char*,char*,char const**) ; 
 int /*<<< orphan*/  avio_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dynarray_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct variant*) ; 
 int /*<<< orphan*/  ff_get_chomp_line (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ff_make_absolute_url (int /*<<< orphan*/ ,int,char const*,char*) ; 
 int /*<<< orphan*/  ff_parse_key_value (char const*,int /*<<< orphan*/ ,struct variant_info*) ; 
 int ffio_open_whitelist (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_segment_list (TYPE_3__*) ; 
 scalar_t__ handle_variant_args ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int parse_playlist(URLContext *h, const char *url)
{
    HLSContext *s = h->priv_data;
    AVIOContext *in;
    int ret = 0, is_segment = 0, is_variant = 0, bandwidth = 0;
    int64_t duration = 0;
    char line[1024];
    const char *ptr;

    if ((ret = ffio_open_whitelist(&in, url, AVIO_FLAG_READ,
                                   &h->interrupt_callback, NULL,
                                   h->protocol_whitelist, h->protocol_blacklist)) < 0)
        return ret;

    ff_get_chomp_line(in, line, sizeof(line));
    if (strcmp(line, "#EXTM3U")) {
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    free_segment_list(s);
    s->finished = 0;
    while (!avio_feof(in)) {
        ff_get_chomp_line(in, line, sizeof(line));
        if (av_strstart(line, "#EXT-X-STREAM-INF:", &ptr)) {
            struct variant_info info = {{0}};
            is_variant = 1;
            ff_parse_key_value(ptr, (ff_parse_key_val_cb) handle_variant_args,
                               &info);
            bandwidth = atoi(info.bandwidth);
        } else if (av_strstart(line, "#EXT-X-TARGETDURATION:", &ptr)) {
            s->target_duration = atoi(ptr) * AV_TIME_BASE;
        } else if (av_strstart(line, "#EXT-X-MEDIA-SEQUENCE:", &ptr)) {
            s->start_seq_no = atoi(ptr);
        } else if (av_strstart(line, "#EXT-X-ENDLIST", &ptr)) {
            s->finished = 1;
        } else if (av_strstart(line, "#EXTINF:", &ptr)) {
            is_segment = 1;
            duration = atof(ptr) * AV_TIME_BASE;
        } else if (av_strstart(line, "#", NULL)) {
            continue;
        } else if (line[0]) {
            if (is_segment) {
                struct segment *seg = av_malloc(sizeof(struct segment));
                if (!seg) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
                seg->duration = duration;
                ff_make_absolute_url(seg->url, sizeof(seg->url), url, line);
                dynarray_add(&s->segments, &s->n_segments, seg);
                is_segment = 0;
            } else if (is_variant) {
                struct variant *var = av_malloc(sizeof(struct variant));
                if (!var) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
                var->bandwidth = bandwidth;
                ff_make_absolute_url(var->url, sizeof(var->url), url, line);
                dynarray_add(&s->variants, &s->n_variants, var);
                is_variant = 0;
            }
        }
    }
    s->last_load_time = av_gettime_relative();

fail:
    avio_close(in);
    return ret;
}