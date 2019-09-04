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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char const*) ; 

int64_t ff_start_tag(AVIOContext *pb, const char *tag)
{
    ffio_wfourcc(pb, tag);
    avio_wl32(pb, -1);
    return avio_tell(pb);
}