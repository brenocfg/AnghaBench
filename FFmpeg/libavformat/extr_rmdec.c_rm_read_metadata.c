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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int /*<<< orphan*/  metadata; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rb16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_rm_metadata ; 
 int /*<<< orphan*/  get_strl (int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static void rm_read_metadata(AVFormatContext *s, AVIOContext *pb, int wide)
{
    char buf[1024];
    int i;

    for (i=0; i<FF_ARRAY_ELEMS(ff_rm_metadata); i++) {
        int len = wide ? avio_rb16(pb) : avio_r8(pb);
        if (len > 0) {
            get_strl(pb, buf, sizeof(buf), len);
            av_dict_set(&s->metadata, ff_rm_metadata[i], buf, 0);
        }
    }
}