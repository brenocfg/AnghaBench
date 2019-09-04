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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RB32 (char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int avio_read (int /*<<< orphan*/ *,char*,unsigned int) ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_tag (char*,unsigned int) ; 

__attribute__((used)) static int check_tag(AVIOContext *s, int offset, unsigned int len)
{
    char tag[4];

    if (len > 4 ||
        avio_seek(s, offset, SEEK_SET) < 0 ||
        avio_read(s, tag, len) < (int)len)
        return -1;
    else if (!AV_RB32(tag) || is_tag(tag, len))
        return 1;

    return 0;
}