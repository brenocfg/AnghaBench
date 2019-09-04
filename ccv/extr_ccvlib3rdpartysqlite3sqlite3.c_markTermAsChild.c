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
struct TYPE_5__ {TYPE_1__* a; } ;
typedef  TYPE_2__ WhereClause ;
struct TYPE_4__ {int iParent; int /*<<< orphan*/  nChild; int /*<<< orphan*/  truthProb; } ;

/* Variables and functions */

__attribute__((used)) static void markTermAsChild(WhereClause *pWC, int iChild, int iParent){
  pWC->a[iChild].iParent = iParent;
  pWC->a[iChild].truthProb = pWC->a[iParent].truthProb;
  pWC->a[iParent].nChild++;
}