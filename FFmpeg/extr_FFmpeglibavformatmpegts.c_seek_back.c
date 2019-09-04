#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {int seekable; } ;
typedef  TYPE_1__ AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ avio_seek (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void seek_back(AVFormatContext *s, AVIOContext *pb, int64_t pos) {

    /* NOTE: We attempt to seek on non-seekable files as well, as the
     * probe buffer usually is big enough. Only warn if the seek failed
     * on files where the seek should work. */
    if (avio_seek(pb, pos, SEEK_SET) < 0)
        av_log(s, (pb->seekable & AVIO_SEEKABLE_NORMAL) ? AV_LOG_ERROR : AV_LOG_INFO, "Unable to seek back to the start\n");
}