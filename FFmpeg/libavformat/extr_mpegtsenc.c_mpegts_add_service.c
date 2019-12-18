#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  default_service_name ;
struct TYPE_17__ {char* value; } ;
struct TYPE_16__ {TYPE_2__* priv_data; } ;
struct TYPE_13__ {int cc; int discontinuity; TYPE_4__* opaque; int /*<<< orphan*/  write_packet; scalar_t__ pid; } ;
struct TYPE_15__ {int sid; int pcr_pid; int /*<<< orphan*/ * program; TYPE_1__ pmt; int /*<<< orphan*/  name; int /*<<< orphan*/  provider_name; } ;
struct TYPE_14__ {int flags; scalar_t__ nb_services; int /*<<< orphan*/  services; scalar_t__ pmt_start_pid; } ;
typedef  TYPE_2__ MpegTSWrite ;
typedef  TYPE_3__ MpegTSService ;
typedef  int /*<<< orphan*/  AVProgram ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 char* DEFAULT_PROVIDER_NAME ; 
 char* DEFAULT_SERVICE_NAME ; 
 int MPEGTS_FLAG_DISCONT ; 
 TYPE_5__* av_dict_get (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ av_dynarray_add_nofree (int /*<<< orphan*/ *,scalar_t__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_free (TYPE_3__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* av_mallocz (int) ; 
 scalar_t__ encode_str8 (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  section_write_packet ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,scalar_t__) ; 

__attribute__((used)) static MpegTSService *mpegts_add_service(AVFormatContext *s, int sid,
                                         const AVDictionary *metadata,
                                         AVProgram *program)
{
    MpegTSWrite *ts = s->priv_data;
    MpegTSService *service;
    AVDictionaryEntry *title, *provider;
    char default_service_name[32];
    const char *service_name;
    const char *provider_name;

    title = av_dict_get(metadata, "service_name", NULL, 0);
    if (!title)
        title = av_dict_get(metadata, "title", NULL, 0);
    snprintf(default_service_name, sizeof(default_service_name), "%s%02d", DEFAULT_SERVICE_NAME, ts->nb_services + 1);
    service_name  = title ? title->value : default_service_name;
    provider      = av_dict_get(metadata, "service_provider", NULL, 0);
    provider_name = provider ? provider->value : DEFAULT_PROVIDER_NAME;

    service = av_mallocz(sizeof(MpegTSService));
    if (!service)
        return NULL;
    service->pmt.pid       = ts->pmt_start_pid + ts->nb_services;
    service->sid           = sid;
    service->pcr_pid       = 0x1fff;
    if (encode_str8(service->provider_name, provider_name) < 0 ||
        encode_str8(service->name, service_name) < 0) {
        av_log(s, AV_LOG_ERROR, "Too long service or provider name\n");
        goto fail;
    }
    if (av_dynarray_add_nofree(&ts->services, &ts->nb_services, service) < 0)
        goto fail;

    service->pmt.write_packet = section_write_packet;
    service->pmt.opaque       = s;
    service->pmt.cc           = 15;
    service->pmt.discontinuity= ts->flags & MPEGTS_FLAG_DISCONT;
    service->program          = program;

    return service;
fail:
    av_free(service);
    return NULL;
}