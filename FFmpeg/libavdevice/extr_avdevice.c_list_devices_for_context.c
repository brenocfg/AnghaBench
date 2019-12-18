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
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  int /*<<< orphan*/  AVDeviceInfoList ;

/* Variables and functions */
 int /*<<< orphan*/  AV_OPT_SEARCH_CHILDREN ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int av_opt_set_dict2 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int avdevice_list_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avformat_free_context (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int list_devices_for_context(AVFormatContext *s, AVDictionary *options,
                                    AVDeviceInfoList **device_list)
{
    AVDictionary *tmp = NULL;
    int ret;

    av_dict_copy(&tmp, options, 0);
    if ((ret = av_opt_set_dict2(s, &tmp, AV_OPT_SEARCH_CHILDREN)) < 0)
        goto fail;
    ret = avdevice_list_devices(s, device_list);
  fail:
    av_dict_free(&tmp);
    avformat_free_context(s);
    return ret;
}