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
struct TYPE_3__ {char* buf; scalar_t__ buf_size; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int /*<<< orphan*/  MAGIC ; 
 int /*<<< orphan*/  memcmp (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_probe(const AVProbeData *pd)
{
    if (pd->buf[0] == 'J' && pd->buf[1] == 'V' && strlen(MAGIC) + 4 <= pd->buf_size &&
        !memcmp(pd->buf + 4, MAGIC, strlen(MAGIC)))
        return AVPROBE_SCORE_MAX;
    return 0;
}