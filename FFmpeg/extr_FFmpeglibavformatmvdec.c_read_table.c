#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
struct TYPE_7__ {int /*<<< orphan*/ * pb; } ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 void* avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_1__*,char*,char*) ; 

__attribute__((used)) static int read_table(AVFormatContext *avctx, AVStream *st,
                       int (*parse)(AVFormatContext *avctx, AVStream *st,
                                    const char *name, int size))
{
    unsigned count;
    int i;

    AVIOContext *pb = avctx->pb;
    avio_skip(pb, 4);
    count = avio_rb32(pb);
    avio_skip(pb, 4);
    for (i = 0; i < count; i++) {
        char name[17];
        int size;

        if (avio_feof(pb))
            return AVERROR_EOF;

        avio_read(pb, name, 16);
        name[sizeof(name) - 1] = 0;
        size = avio_rb32(pb);
        if (size < 0) {
            av_log(avctx, AV_LOG_ERROR, "entry size %d is invalid\n", size);
            return AVERROR_INVALIDDATA;
        }
        if (parse(avctx, st, name, size) < 0) {
            avpriv_request_sample(avctx, "Variable %s", name);
            avio_skip(pb, size);
        }
    }
    return 0;
}