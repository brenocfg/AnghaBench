#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {char* value; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_1__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* get_metadata_lang (int /*<<< orphan*/ *,char*,int*) ; 
 scalar_t__ strlen (char const*) ; 
 double strtod (char const*,char**) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_loci_tag(AVFormatContext *s, AVIOContext *pb)
{
    int lang;
    int64_t pos = avio_tell(pb);
    double latitude, longitude, altitude;
    int32_t latitude_fix, longitude_fix, altitude_fix;
    AVDictionaryEntry *t = get_metadata_lang(s, "location", &lang);
    const char *ptr, *place = "";
    char *end;
    static const char *astronomical_body = "earth";
    if (!t)
        return 0;

    ptr = t->value;
    longitude = strtod(ptr, &end);
    if (end == ptr) {
        av_log(s, AV_LOG_WARNING, "malformed location metadata\n");
        return 0;
    }
    ptr = end;
    latitude = strtod(ptr, &end);
    if (end == ptr) {
        av_log(s, AV_LOG_WARNING, "malformed location metadata\n");
        return 0;
    }
    ptr = end;
    altitude = strtod(ptr, &end);
    /* If no altitude was present, the default 0 should be fine */
    if (*end == '/')
        place = end + 1;

    latitude_fix  = (int32_t) ((1 << 16) * latitude);
    longitude_fix = (int32_t) ((1 << 16) * longitude);
    altitude_fix  = (int32_t) ((1 << 16) * altitude);

    avio_wb32(pb, 0);         /* size */
    ffio_wfourcc(pb, "loci"); /* type */
    avio_wb32(pb, 0);         /* version + flags */
    avio_wb16(pb, lang);
    avio_write(pb, place, strlen(place) + 1);
    avio_w8(pb, 0);           /* role of place (0 == shooting location, 1 == real location, 2 == fictional location) */
    avio_wb32(pb, latitude_fix);
    avio_wb32(pb, longitude_fix);
    avio_wb32(pb, altitude_fix);
    avio_write(pb, astronomical_body, strlen(astronomical_body) + 1);
    avio_w8(pb, 0);           /* additional notes, null terminated string */

    return update_size(pb, pos);
}