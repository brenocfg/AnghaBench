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
struct TYPE_4__ {scalar_t__ dstXYZ; scalar_t__ srcXYZ; int /*<<< orphan*/  dstFormat; int /*<<< orphan*/  srcFormat; int /*<<< orphan*/  dst0Alpha; int /*<<< orphan*/  src0Alpha; } ;
typedef  TYPE_1__ SwsContext ;

/* Variables and functions */
 int /*<<< orphan*/  fill_xyztables (TYPE_1__*) ; 
 int /*<<< orphan*/  handle_0alpha (int /*<<< orphan*/ *) ; 
 scalar_t__ handle_xyz (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_formats(SwsContext *c)
{
    c->src0Alpha |= handle_0alpha(&c->srcFormat);
    c->dst0Alpha |= handle_0alpha(&c->dstFormat);
    c->srcXYZ    |= handle_xyz(&c->srcFormat);
    c->dstXYZ    |= handle_xyz(&c->dstFormat);
    if (c->srcXYZ || c->dstXYZ)
        fill_xyztables(c);
}