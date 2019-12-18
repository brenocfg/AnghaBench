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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  LXF_IDENT ; 
 int LXF_IDENT_LENGTH ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_r8 (int /*<<< orphan*/ ) ; 
 int avio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lxf_sync(AVFormatContext *s, uint8_t *header)
{
    uint8_t buf[LXF_IDENT_LENGTH];
    int ret;

    if ((ret = avio_read(s->pb, buf, LXF_IDENT_LENGTH)) != LXF_IDENT_LENGTH)
        return ret < 0 ? ret : AVERROR_EOF;

    while (memcmp(buf, LXF_IDENT, LXF_IDENT_LENGTH)) {
        if (avio_feof(s->pb))
            return AVERROR_EOF;

        memmove(buf, &buf[1], LXF_IDENT_LENGTH-1);
        buf[LXF_IDENT_LENGTH-1] = avio_r8(s->pb);
    }

    memcpy(header, LXF_IDENT, LXF_IDENT_LENGTH);

    return 0;
}