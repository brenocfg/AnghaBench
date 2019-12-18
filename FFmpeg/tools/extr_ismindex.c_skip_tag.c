#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ expect_tag (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int skip_tag(AVIOContext *in, int32_t tag_name)
{
    int64_t pos = avio_tell(in);
    int32_t size, tag;

    size = avio_rb32(in);
    tag  = avio_rb32(in);
    if (expect_tag(tag, tag_name) != 0)
        return -1;
    avio_seek(in, pos + size, SEEK_SET);
    return 0;
}