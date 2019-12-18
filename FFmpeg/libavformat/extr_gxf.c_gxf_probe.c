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
typedef  int /*<<< orphan*/  startcode ;
typedef  int /*<<< orphan*/  endcode ;
struct TYPE_3__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int const*,int) ; 

__attribute__((used)) static int gxf_probe(const AVProbeData *p) {
    static const uint8_t startcode[] = {0, 0, 0, 0, 1, 0xbc}; // start with map packet
    static const uint8_t endcode[] = {0, 0, 0, 0, 0xe1, 0xe2};
    if (!memcmp(p->buf, startcode, sizeof(startcode)) &&
        !memcmp(&p->buf[16 - sizeof(endcode)], endcode, sizeof(endcode)))
        return AVPROBE_SCORE_MAX;
    return 0;
}