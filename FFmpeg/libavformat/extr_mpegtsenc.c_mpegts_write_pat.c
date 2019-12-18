#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {TYPE_2__* priv_data; } ;
struct TYPE_6__ {int pid; } ;
struct TYPE_8__ {int sid; TYPE_1__ pmt; } ;
struct TYPE_7__ {int nb_services; int /*<<< orphan*/  tables_version; int /*<<< orphan*/  tsid; int /*<<< orphan*/  pat; TYPE_3__** services; } ;
typedef  TYPE_2__ MpegTSWrite ;
typedef  TYPE_3__ MpegTSService ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  PAT_TID ; 
 int SECTION_LENGTH ; 
 int /*<<< orphan*/  mpegts_write_section1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put16 (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static void mpegts_write_pat(AVFormatContext *s)
{
    MpegTSWrite *ts = s->priv_data;
    MpegTSService *service;
    uint8_t data[SECTION_LENGTH], *q;
    int i;

    q = data;
    for (i = 0; i < ts->nb_services; i++) {
        service = ts->services[i];
        put16(&q, service->sid);
        put16(&q, 0xe000 | service->pmt.pid);
    }
    mpegts_write_section1(&ts->pat, PAT_TID, ts->tsid, ts->tables_version, 0, 0,
                          data, q - data);
}