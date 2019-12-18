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
struct TYPE_3__ {int alloc; int n; int /*<<< orphan*/ * z; } ;
typedef  TYPE_1__ SString ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

void SStringShrink(SString* pStr) {
  if (pStr->alloc > (pStr->n + 1) && pStr->alloc > (pStr->n * 2)) {
    pStr->z = realloc(pStr->z, pStr->n + 1);
    assert(pStr->z != NULL);

    pStr->alloc = pStr->n + 1;
  }
}