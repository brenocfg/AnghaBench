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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  order; } ;
struct TYPE_5__ {TYPE_1__ cur; } ;
typedef  TYPE_2__ STSBuf ;

/* Variables and functions */

void tsBufSetTraverseOrder(STSBuf* pTSBuf, int32_t order) {
  if (pTSBuf == NULL) {
    return;
  }

  pTSBuf->cur.order = order;
}