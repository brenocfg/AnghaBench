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
typedef  int /*<<< orphan*/  ff_asf_guid ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ff_get_guid(AVIOContext *s, ff_asf_guid *g)
{
    int ret;
    av_assert0(sizeof(*g) == 16); //compiler will optimize this out
    ret = avio_read(s, *g, sizeof(*g));
    if (ret < (int)sizeof(*g)) {
        memset(*g, 0, sizeof(*g));
        return ret < 0 ? ret : AVERROR_INVALIDDATA;
    }
    return 0;
}