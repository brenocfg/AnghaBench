#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  UID ;
struct TYPE_2__ {int /*<<< orphan*/ * fc; } ;
typedef  TYPE_1__ MXFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 scalar_t__ IS_KLV_KEY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_STR_METADATA (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  mxf_avid_project_name ; 

__attribute__((used)) static int mxf_read_preface_metadata(void *arg, AVIOContext *pb, int tag, int size, UID uid, int64_t klv_offset)
{
    MXFContext *mxf = arg;
    AVFormatContext *s = mxf->fc;
    int ret;
    char *str = NULL;

    if (tag >= 0x8000 && (IS_KLV_KEY(uid, mxf_avid_project_name))) {
        SET_STR_METADATA(pb, "project_name", str);
    }
    return 0;
}