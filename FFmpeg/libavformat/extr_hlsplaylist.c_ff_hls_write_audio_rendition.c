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
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ *,char*,...) ; 

void ff_hls_write_audio_rendition(AVIOContext *out, char *agroup,
                                  const char *filename, char *language, int name_id, int is_default) {
    if (!out || !agroup || !filename)
        return;

    avio_printf(out, "#EXT-X-MEDIA:TYPE=AUDIO,GROUP-ID=\"group_%s\"", agroup);
    avio_printf(out, ",NAME=\"audio_%d\",DEFAULT=%s,", name_id, is_default ? "YES" : "NO");
    if (language) {
        avio_printf(out, "LANGUAGE=\"%s\",", language);
    }
    avio_printf(out, "URI=\"%s\"\n", filename);
}