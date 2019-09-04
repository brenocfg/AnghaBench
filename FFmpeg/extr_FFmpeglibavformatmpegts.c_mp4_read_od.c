#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int descr_count; int /*<<< orphan*/  pb; } ;
typedef  int /*<<< orphan*/  Mp4Descr ;
typedef  TYPE_1__ MP4DescrParseContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int init_MP4DescrParseContext (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int) ; 
 int parse_mp4_descr_arr (TYPE_1__*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mp4_read_od(AVFormatContext *s, const uint8_t *buf, unsigned size,
                       Mp4Descr *descr, int *descr_count, int max_descr_count)
{
    MP4DescrParseContext d;
    int ret;

    ret = init_MP4DescrParseContext(&d, s, buf, size, descr, max_descr_count);
    if (ret < 0)
        return ret;

    ret = parse_mp4_descr_arr(&d, avio_tell(&d.pb), size);

    *descr_count = d.descr_count;
    return ret;
}