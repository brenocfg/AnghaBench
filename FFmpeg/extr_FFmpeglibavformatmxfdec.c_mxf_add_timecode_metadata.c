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
typedef  int /*<<< orphan*/  AVTimecode ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AV_TIMECODE_STR_SIZE ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_timecode_make_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxf_add_timecode_metadata(AVDictionary **pm, const char *key, AVTimecode *tc)
{
    char buf[AV_TIMECODE_STR_SIZE];
    av_dict_set(pm, key, av_timecode_make_string(tc, buf, 0), 0);

    return 0;
}