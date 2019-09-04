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
struct TYPE_3__ {scalar_t__ buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RL32 (scalar_t__) ; 
 int MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  MLV_VERSION ; 
 int /*<<< orphan*/  memcmp (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int probe(const AVProbeData *p)
{
    if (AV_RL32(p->buf) == MKTAG('M','L','V','I') &&
        AV_RL32(p->buf + 4) >= 52 &&
        !memcmp(p->buf + 8, MLV_VERSION, 5))
        return AVPROBE_SCORE_MAX;
    return 0;
}