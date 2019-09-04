#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  place ;
typedef  int /*<<< orphan*/  key2 ;
typedef  float int32_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/  event_flags; } ;
struct TYPE_4__ {TYPE_3__* fc; } ;
typedef  TYPE_1__ MOVContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVFMT_EVENT_FLAG_METADATA_UPDATED ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int av_dict_set (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_strlcatf (char*,int,char*,...) ; 
 scalar_t__ avio_get_str (int /*<<< orphan*/ *,unsigned int,char*,int) ; 
 int /*<<< orphan*/  avio_rb16 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_mov_lang_to_iso639 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int mov_metadata_loci(MOVContext *c, AVIOContext *pb, unsigned len)
{
    char language[4] = { 0 };
    char buf[200], place[100];
    uint16_t langcode = 0;
    double longitude, latitude, altitude;
    const char *key = "location";

    if (len < 4 + 2 + 1 + 1 + 4 + 4 + 4) {
        av_log(c->fc, AV_LOG_ERROR, "loci too short\n");
        return AVERROR_INVALIDDATA;
    }

    avio_skip(pb, 4); // version+flags
    langcode = avio_rb16(pb);
    ff_mov_lang_to_iso639(langcode, language);
    len -= 6;

    len -= avio_get_str(pb, len, place, sizeof(place));
    if (len < 1) {
        av_log(c->fc, AV_LOG_ERROR, "place name too long\n");
        return AVERROR_INVALIDDATA;
    }
    avio_skip(pb, 1); // role
    len -= 1;

    if (len < 12) {
        av_log(c->fc, AV_LOG_ERROR,
               "loci too short (%u bytes left, need at least %d)\n", len, 12);
        return AVERROR_INVALIDDATA;
    }
    longitude = ((int32_t) avio_rb32(pb)) / (float) (1 << 16);
    latitude  = ((int32_t) avio_rb32(pb)) / (float) (1 << 16);
    altitude  = ((int32_t) avio_rb32(pb)) / (float) (1 << 16);

    // Try to output in the same format as the ?xyz field
    snprintf(buf, sizeof(buf), "%+08.4f%+09.4f",  latitude, longitude);
    if (altitude)
        av_strlcatf(buf, sizeof(buf), "%+f", altitude);
    av_strlcatf(buf, sizeof(buf), "/%s", place);

    if (*language && strcmp(language, "und")) {
        char key2[16];
        snprintf(key2, sizeof(key2), "%s-%s", key, language);
        av_dict_set(&c->fc->metadata, key2, buf, 0);
    }
    c->fc->event_flags |= AVFMT_EVENT_FLAG_METADATA_UPDATED;
    return av_dict_set(&c->fc->metadata, key, buf, 0);
}