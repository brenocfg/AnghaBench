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
struct TYPE_4__ {int /*<<< orphan*/  pSchema; } ;
typedef  TYPE_1__ tOrderDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  tColModelDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfree (TYPE_1__*) ; 

void tOrderDescDestroy(tOrderDescriptor *pDesc) {
  if (pDesc == NULL) {
    return;
  }

  tColModelDestroy(pDesc->pSchema);
  tfree(pDesc);
}