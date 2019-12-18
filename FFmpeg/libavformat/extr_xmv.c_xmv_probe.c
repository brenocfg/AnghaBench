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
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__ buf_size; scalar_t__ buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RL32 (scalar_t__) ; 
 scalar_t__ XMV_MIN_HEADER_SIZE ; 
 int /*<<< orphan*/  memcmp (scalar_t__,char*,int) ; 

__attribute__((used)) static int xmv_probe(const AVProbeData *p)
{
    uint32_t file_version;

    if (p->buf_size < XMV_MIN_HEADER_SIZE)
        return 0;

    file_version = AV_RL32(p->buf + 16);
    if ((file_version == 0) || (file_version > 4))
        return 0;

    if (!memcmp(p->buf + 12, "xobX", 4))
        return AVPROBE_SCORE_MAX;

    return 0;
}