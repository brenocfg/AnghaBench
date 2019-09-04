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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int nb_streams; int /*<<< orphan*/ * tracks; } ;
typedef  TYPE_1__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mov_write_trex_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_mvex_tag(AVIOContext *pb, MOVMuxContext *mov)
{
    int64_t pos = avio_tell(pb);
    int i;
    avio_wb32(pb, 0x0); /* size */
    ffio_wfourcc(pb, "mvex");
    for (i = 0; i < mov->nb_streams; i++)
        mov_write_trex_tag(pb, &mov->tracks[i]);
    return update_size(pb, pos);
}