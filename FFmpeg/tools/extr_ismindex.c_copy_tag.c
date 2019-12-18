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
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int FFMIN (int,scalar_t__) ; 
 scalar_t__ avio_rb32 (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ expect_tag (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int copy_tag(AVIOContext *in, AVIOContext *out, int32_t tag_name)
{
    int32_t size, tag;

    size = avio_rb32(in);
    tag  = avio_rb32(in);
    avio_wb32(out, size);
    avio_wb32(out, tag);
    if (expect_tag(tag, tag_name) != 0)
        return -1;
    size -= 8;
    while (size > 0) {
        char buf[1024];
        int len = FFMIN(sizeof(buf), size);
        int got;
        if ((got = avio_read(in, buf, len)) != len) {
            fprintf(stderr, "short read, wanted %d, got %d\n", len, got);
            break;
        }
        avio_write(out, buf, len);
        size -= len;
    }
    return 0;
}