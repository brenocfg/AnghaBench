#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* priv_data; } ;
struct TYPE_11__ {scalar_t__ pid; } ;
struct TYPE_13__ {int sid; int pcr_pid; int /*<<< orphan*/  name; int /*<<< orphan*/  provider_name; TYPE_1__ pmt; } ;
struct TYPE_12__ {scalar_t__ nb_services; int /*<<< orphan*/  services; scalar_t__ pmt_start_pid; } ;
typedef  TYPE_2__ MpegTSWrite ;
typedef  TYPE_3__ MpegTSService ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ av_dynarray_add_nofree (int /*<<< orphan*/ *,scalar_t__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_free (TYPE_3__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* av_mallocz (int) ; 
 scalar_t__ encode_str8 (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static MpegTSService *mpegts_add_service(AVFormatContext *s, int sid,
                                         const char *provider_name,
                                         const char *name)
{
    MpegTSWrite *ts = s->priv_data;
    MpegTSService *service;

    service = av_mallocz(sizeof(MpegTSService));
    if (!service)
        return NULL;
    service->pmt.pid       = ts->pmt_start_pid + ts->nb_services;
    service->sid           = sid;
    service->pcr_pid       = 0x1fff;
    if (encode_str8(service->provider_name, provider_name) < 0 ||
        encode_str8(service->name, name) < 0) {
        av_log(s, AV_LOG_ERROR, "Too long service or provider name\n");
        goto fail;
    }
    if (av_dynarray_add_nofree(&ts->services, &ts->nb_services, service) < 0)
        goto fail;

    return service;
fail:
    av_free(service);
    return NULL;
}