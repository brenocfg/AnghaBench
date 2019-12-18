#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cxgbi_pagepod {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct cxgbi_pagepod*,int /*<<< orphan*/ ,int) ; 

void cxgbi_ddp_ppod_clear(struct cxgbi_pagepod *ppod)
{
	memset(ppod, 0, sizeof(*ppod));
}