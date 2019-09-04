#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  temp_filename ;
typedef  int /*<<< orphan*/  filename ;
struct TYPE_13__ {char* url; int (* io_open ) (TYPE_4__*,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_1__** streams; TYPE_3__* priv_data; } ;
struct TYPE_12__ {int nb_streams; TYPE_2__* streams; } ;
struct TYPE_11__ {double last_ts; int bitrate; int /*<<< orphan*/  metadata_size; int /*<<< orphan*/  metadata; } ;
struct TYPE_10__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_2__ OutputStream ;
typedef  TYPE_3__ HDSContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int AV_BASE64_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_base64_encode (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_basename (char*) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,char*) ; 
 char* av_malloc (int) ; 
 double av_q2d (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ff_format_io_close (TYPE_4__*,int /*<<< orphan*/ **) ; 
 int ff_rename (char*,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int stub1 (TYPE_4__*,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_manifest(AVFormatContext *s, int final)
{
    HDSContext *c = s->priv_data;
    AVIOContext *out;
    char filename[1024], temp_filename[1024];
    int ret, i;
    double duration = 0;

    if (c->nb_streams > 0)
        duration = c->streams[0].last_ts * av_q2d(s->streams[0]->time_base);

    snprintf(filename, sizeof(filename), "%s/index.f4m", s->url);
    snprintf(temp_filename, sizeof(temp_filename), "%s/index.f4m.tmp", s->url);
    ret = s->io_open(s, &out, temp_filename, AVIO_FLAG_WRITE, NULL);
    if (ret < 0) {
        av_log(s, AV_LOG_ERROR, "Unable to open %s for writing\n", temp_filename);
        return ret;
    }
    avio_printf(out, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
    avio_printf(out, "<manifest xmlns=\"http://ns.adobe.com/f4m/1.0\">\n");
    avio_printf(out, "\t<id>%s</id>\n", av_basename(s->url));
    avio_printf(out, "\t<streamType>%s</streamType>\n",
                     final ? "recorded" : "live");
    avio_printf(out, "\t<deliveryType>streaming</deliveryType>\n");
    if (final)
        avio_printf(out, "\t<duration>%f</duration>\n", duration);
    for (i = 0; i < c->nb_streams; i++) {
        OutputStream *os = &c->streams[i];
        int b64_size = AV_BASE64_SIZE(os->metadata_size);
        char *base64 = av_malloc(b64_size);
        if (!base64) {
            ff_format_io_close(s, &out);
            return AVERROR(ENOMEM);
        }
        av_base64_encode(base64, b64_size, os->metadata, os->metadata_size);

        avio_printf(out, "\t<bootstrapInfo profile=\"named\" url=\"stream%d.abst\" id=\"bootstrap%d\" />\n", i, i);
        avio_printf(out, "\t<media bitrate=\"%d\" url=\"stream%d\" bootstrapInfoId=\"bootstrap%d\">\n", os->bitrate/1000, i, i);
        avio_printf(out, "\t\t<metadata>%s</metadata>\n", base64);
        avio_printf(out, "\t</media>\n");
        av_free(base64);
    }
    avio_printf(out, "</manifest>\n");
    avio_flush(out);
    ff_format_io_close(s, &out);
    return ff_rename(temp_filename, filename, s);
}