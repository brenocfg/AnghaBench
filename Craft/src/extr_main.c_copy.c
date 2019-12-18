#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  block1; int /*<<< orphan*/  copy1; int /*<<< orphan*/  block0; int /*<<< orphan*/  copy0; } ;
typedef  int /*<<< orphan*/  Block ;

/* Variables and functions */
 TYPE_1__* g ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void copy() {
    memcpy(&g->copy0, &g->block0, sizeof(Block));
    memcpy(&g->copy1, &g->block1, sizeof(Block));
}