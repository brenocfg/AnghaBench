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
struct TYPE_3__ {int /*<<< orphan*/  hwaccel_device; } ;
typedef  TYPE_1__ InputStream ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_HWDEVICE_TYPE_QSV ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int av_dict_set (int /*<<< orphan*/ **,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int av_hwdevice_ctx_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hw_device_ctx ; 
 scalar_t__ qsv_device ; 

__attribute__((used)) static int qsv_device_init(InputStream *ist)
{
    int err;
    AVDictionary *dict = NULL;

    if (qsv_device) {
        err = av_dict_set(&dict, "child_device", qsv_device, 0);
        if (err < 0)
            return err;
    }

    err = av_hwdevice_ctx_create(&hw_device_ctx, AV_HWDEVICE_TYPE_QSV,
                                 ist->hwaccel_device, dict, 0);
    if (err < 0) {
        av_log(NULL, AV_LOG_ERROR, "Error creating a QSV device\n");
        goto err_out;
    }

err_out:
    if (dict)
        av_dict_free(&dict);

    return err;
}