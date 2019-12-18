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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  Data4; int /*<<< orphan*/  Data2; int /*<<< orphan*/  Data1; } ;
typedef  TYPE_1__ GUID ;

/* Variables and functions */
 int /*<<< orphan*/  dshowdebug (char*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

void ff_printGUID(const GUID *g)
{
#if DSHOWDEBUG
    const uint32_t *d = (const uint32_t *) &g->Data1;
    const uint16_t *w = (const uint16_t *) &g->Data2;
    const uint8_t  *c = (const uint8_t  *) &g->Data4;

    dshowdebug("0x%08x 0x%04x 0x%04x %02x%02x%02x%02x%02x%02x%02x%02x",
               d[0], w[0], w[1],
               c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);
#endif
}