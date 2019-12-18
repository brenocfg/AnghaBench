#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {scalar_t__* name; scalar_t__* provider_name; int /*<<< orphan*/  sid; } ;
struct TYPE_5__ {int nb_services; int /*<<< orphan*/  tables_version; int /*<<< orphan*/  tsid; int /*<<< orphan*/  sdt; int /*<<< orphan*/  service_type; TYPE_2__** services; int /*<<< orphan*/  onid; } ;
typedef  TYPE_1__ MpegTSWrite ;
typedef  TYPE_2__ MpegTSService ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SDT_TID ; 
 int SECTION_LENGTH ; 
 int /*<<< orphan*/  mpegts_write_section1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  put16 (int**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putbuf (int**,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static void mpegts_write_sdt(AVFormatContext *s)
{
    MpegTSWrite *ts = s->priv_data;
    MpegTSService *service;
    uint8_t data[SECTION_LENGTH], *q, *desc_list_len_ptr, *desc_len_ptr;
    int i, running_status, free_ca_mode, val;

    q = data;
    put16(&q, ts->onid);
    *q++ = 0xff;
    for (i = 0; i < ts->nb_services; i++) {
        service = ts->services[i];
        put16(&q, service->sid);
        *q++              = 0xfc | 0x00; /* currently no EIT info */
        desc_list_len_ptr = q;
        q                += 2;
        running_status    = 4; /* running */
        free_ca_mode      = 0;

        /* write only one descriptor for the service name and provider */
        *q++         = 0x48;
        desc_len_ptr = q;
        q++;
        *q++         = ts->service_type;
        putbuf(&q, service->provider_name, service->provider_name[0] + 1);
        putbuf(&q, service->name, service->name[0] + 1);
        desc_len_ptr[0] = q - desc_len_ptr - 1;

        /* fill descriptor length */
        val = (running_status << 13) | (free_ca_mode << 12) |
              (q - desc_list_len_ptr - 2);
        desc_list_len_ptr[0] = val >> 8;
        desc_list_len_ptr[1] = val;
    }
    mpegts_write_section1(&ts->sdt, SDT_TID, ts->tsid, ts->tables_version, 0, 0,
                          data, q - data);
}