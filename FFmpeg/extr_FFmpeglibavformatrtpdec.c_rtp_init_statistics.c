#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int probation; int /*<<< orphan*/  max_seq; } ;
typedef  TYPE_1__ RTPStatistics ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtp_init_statistics(RTPStatistics *s, uint16_t base_sequence)
{
    memset(s, 0, sizeof(RTPStatistics));
    s->max_seq   = base_sequence;
    s->probation = 1;
}