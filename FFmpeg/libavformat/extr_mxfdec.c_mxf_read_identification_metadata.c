#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ UID ;
struct TYPE_6__ {int /*<<< orphan*/ * fc; } ;
typedef  TYPE_2__ MXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SET_STR_METADATA (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  SET_TS_METADATA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SET_UID_METADATA (int /*<<< orphan*/ *,char*,TYPE_1__,char*) ; 

__attribute__((used)) static int mxf_read_identification_metadata(void *arg, AVIOContext *pb, int tag, int size, UID _uid, int64_t klv_offset)
{
    MXFContext *mxf = arg;
    AVFormatContext *s = mxf->fc;
    int ret;
    UID uid = { 0 };
    char *str = NULL;
    uint64_t ts;
    switch (tag) {
    case 0x3C01:
        SET_STR_METADATA(pb, "company_name", str);
        break;
    case 0x3C02:
        SET_STR_METADATA(pb, "product_name", str);
        break;
    case 0x3C04:
        SET_STR_METADATA(pb, "product_version", str);
        break;
    case 0x3C05:
        SET_UID_METADATA(pb, "product_uid", uid, str);
        break;
    case 0x3C06:
        SET_TS_METADATA(pb, "modification_date", ts, str);
        break;
    case 0x3C08:
        SET_STR_METADATA(pb, "application_platform", str);
        break;
    case 0x3C09:
        SET_UID_METADATA(pb, "generation_uid", uid, str);
        break;
    case 0x3C0A:
        SET_UID_METADATA(pb, "uid", uid, str);
        break;
    }
    return 0;
}