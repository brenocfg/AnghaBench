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
 int AV_RL16 (scalar_t__) ; 
 scalar_t__ AV_RL32 (scalar_t__) ; 
 scalar_t__ MKTAG (char,char,char,char) ; 

__attribute__((used)) static int probe(const AVProbeData *p)
{
    if (AV_RL32(p->buf) == MKTAG('R','S','T','M') &&
        (AV_RL16(p->buf + 4) == 0xFFFE ||
         AV_RL16(p->buf + 4) == 0xFEFF))
        return AVPROBE_SCORE_MAX / 3 * 2;
    return 0;
}