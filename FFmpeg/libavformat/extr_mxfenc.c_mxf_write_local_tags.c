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
struct TYPE_3__ {int /*<<< orphan*/  uid; int /*<<< orphan*/  local_tag; } ;
typedef  TYPE_1__ MXFLocalTagPair ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mxf_write_local_tags(AVIOContext *pb, const MXFLocalTagPair *local_tags, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        avio_wb16(pb, local_tags[i].local_tag);
        avio_write(pb, local_tags[i].uid, 16);
    }
}