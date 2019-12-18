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
struct TYPE_5__ {scalar_t__ n; scalar_t__ alloc; int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ SString ;

/* Variables and functions */
 int /*<<< orphan*/  calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void SStringCopy(SString* pDest, const SString* pSrc) {
  if (pSrc->n > 0) {
    pDest->n = pSrc->n;
    pDest->alloc = pDest->n + 1;  // one additional space for null terminate

    pDest->z = calloc(1, pDest->alloc);

    memcpy(pDest->z, pSrc->z, pDest->n);
  } else {
    memset(pDest, 0, sizeof(SString));
  }
}