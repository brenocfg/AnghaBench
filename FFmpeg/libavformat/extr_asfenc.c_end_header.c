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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void end_header(AVIOContext *pb, int64_t pos)
{
    int64_t pos1;

    pos1 = avio_tell(pb);
    avio_seek(pb, pos + 16, SEEK_SET);
    avio_wl64(pb, pos1 - pos);
    avio_seek(pb, pos1, SEEK_SET);
}