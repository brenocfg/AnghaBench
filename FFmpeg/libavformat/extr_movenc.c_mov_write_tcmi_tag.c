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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_tcmi_tag(AVIOContext *pb, MOVTrack *track)
{
    int64_t pos = avio_tell(pb);
    const char *font = "Lucida Grande";
    avio_wb32(pb, 0);                   /* size */
    ffio_wfourcc(pb, "tcmi");           /* timecode media information atom */
    avio_wb32(pb, 0);                   /* version & flags */
    avio_wb16(pb, 0);                   /* text font */
    avio_wb16(pb, 0);                   /* text face */
    avio_wb16(pb, 12);                  /* text size */
    avio_wb16(pb, 0);                   /* (unknown, not in the QT specs...) */
    avio_wb16(pb, 0x0000);              /* text color (red) */
    avio_wb16(pb, 0x0000);              /* text color (green) */
    avio_wb16(pb, 0x0000);              /* text color (blue) */
    avio_wb16(pb, 0xffff);              /* background color (red) */
    avio_wb16(pb, 0xffff);              /* background color (green) */
    avio_wb16(pb, 0xffff);              /* background color (blue) */
    avio_w8(pb, strlen(font));          /* font len (part of the pascal string) */
    avio_write(pb, font, strlen(font)); /* font name */
    return update_size(pb, pos);
}