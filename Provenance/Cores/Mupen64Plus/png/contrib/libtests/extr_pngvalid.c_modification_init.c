#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ add; int /*<<< orphan*/ * modify_fn; scalar_t__ chunk; int /*<<< orphan*/ * next; } ;
typedef  TYPE_1__ png_modification ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  modification_reset (TYPE_1__*) ; 

__attribute__((used)) static void
modification_init(png_modification *pmm)
{
   memset(pmm, 0, sizeof *pmm);
   pmm->next = NULL;
   pmm->chunk = 0;
   pmm->modify_fn = NULL;
   pmm->add = 0;
   modification_reset(pmm);
}