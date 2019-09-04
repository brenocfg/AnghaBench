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
typedef  char uint8_t ;
struct TYPE_3__ {char* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RB64 (char const*) ; 

__attribute__((used)) static int xpm_probe(const AVProbeData *p)
{
    const uint8_t *b = p->buf;

    if (AV_RB64(b) == 0x2f2a2058504d202a && *(b+8) == '/')
        return AVPROBE_SCORE_MAX - 1;
    return 0;
}