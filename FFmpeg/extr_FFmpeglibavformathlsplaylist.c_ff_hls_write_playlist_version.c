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

void ff_hls_write_playlist_version(AVIOContext *out, int version) {
    if (!out)
        return;
    avio_printf(out, "#EXTM3U\n");
    avio_printf(out, "#EXT-X-VERSION:%d\n", version);
}