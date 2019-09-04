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
typedef  int /*<<< orphan*/  ff_asf_guid ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_put_guid (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int64_t put_header(AVIOContext *pb, const ff_asf_guid *g)
{
    int64_t pos;

    pos = avio_tell(pb);
    ff_put_guid(pb, g);
    avio_wl64(pb, 24);
    return pos;
}