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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  ifv_magic ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int const*,int) ; 

__attribute__((used)) static int ifv_probe(const AVProbeData *p)
{
    static const uint8_t ifv_magic[] = {0x11, 0xd2, 0xd3, 0xab, 0xba, 0xa9,
        0xcf, 0x11, 0x8e, 0xe6, 0x00, 0xc0, 0x0c, 0x20, 0x53, 0x65, 0x44};

    if (!memcmp(p->buf, ifv_magic, sizeof(ifv_magic)))
        return AVPROBE_SCORE_MAX;

    return 0;
}