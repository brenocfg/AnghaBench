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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  mov_write_string_data_tag (int /*<<< orphan*/ *,char const*,int,int) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_string_tag(AVIOContext *pb, const char *name,
                                const char *value, int lang, int long_style)
{
    int size = 0;
    if (value && value[0]) {
        int64_t pos = avio_tell(pb);
        avio_wb32(pb, 0); /* size */
        ffio_wfourcc(pb, name);
        mov_write_string_data_tag(pb, value, lang, long_style);
        size = update_size(pb, pos);
    }
    return size;
}