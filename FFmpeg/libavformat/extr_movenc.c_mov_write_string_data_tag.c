#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,char const*,int) ; 
 int ff_mov_iso639_to_lang (char*,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int mov_write_string_data_tag(AVIOContext *pb, const char *data, int lang, int long_style)
{
    if (long_style) {
        int size = 16 + strlen(data);
        avio_wb32(pb, size); /* size */
        ffio_wfourcc(pb, "data");
        avio_wb32(pb, 1);
        avio_wb32(pb, 0);
        avio_write(pb, data, strlen(data));
        return size;
    } else {
        if (!lang)
            lang = ff_mov_iso639_to_lang("und", 1);
        avio_wb16(pb, strlen(data)); /* string length */
        avio_wb16(pb, lang);
        avio_write(pb, data, strlen(data));
        return strlen(data) + 4;
    }
}