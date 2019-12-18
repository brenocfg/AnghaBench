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
typedef  int /*<<< orphan*/  tSkipListKey ;
typedef  int /*<<< orphan*/  pKey ;
typedef  int int32_t ;
typedef  int (* __compar_fn_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int,int,int (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 

__attribute__((used)) static void removeDuplicateKey(tSkipListKey *pKey, int32_t *numOfKey, __compar_fn_t comparator) {
  if (*numOfKey == 1) {
    return;
  }

  qsort(pKey, *numOfKey, sizeof(pKey[0]), comparator);
  int32_t i = 0, j = 1;

  while (i < (*numOfKey) && j < (*numOfKey)) {
    int32_t ret = comparator(&pKey[i], &pKey[j]);
    if (ret == 0) {
      j++;
    } else {
      pKey[i + 1] = pKey[j];
      i++;
      j++;
    }
  }

  (*numOfKey) = i + 1;
}