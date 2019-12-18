#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  base; scalar_t__ offset; scalar_t__ level; } ;
struct TYPE_5__ {TYPE_1__ peak; } ;
typedef  TYPE_2__ CFHDContext ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_peak_table_defaults(CFHDContext *s)
{
    s->peak.level  = 0;
    s->peak.offset = 0;
    memset(&s->peak.base, 0, sizeof(s->peak.base));
}