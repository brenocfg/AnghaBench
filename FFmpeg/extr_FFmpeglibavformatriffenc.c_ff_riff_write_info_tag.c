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
 size_t UINT32_MAX ; 
 int /*<<< orphan*/  avio_put_str (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char const*) ; 
 size_t strlen (char const*) ; 

void ff_riff_write_info_tag(AVIOContext *pb, const char *tag, const char *str)
{
    size_t len = strlen(str);
    if (len > 0 && len < UINT32_MAX) {
        len++;
        ffio_wfourcc(pb, tag);
        avio_wl32(pb, len);
        avio_put_str(pb, str);
        if (len & 1)
            avio_w8(pb, 0);
    }
}