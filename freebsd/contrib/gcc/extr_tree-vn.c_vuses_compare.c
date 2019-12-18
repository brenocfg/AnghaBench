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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int SSA_NAME_VERSION (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
vuses_compare (const void *pa, const void *pb)
{
  const tree vusea = *((const tree *)pa);
  const tree vuseb = *((const tree *)pb);
  int sn = SSA_NAME_VERSION (vusea) - SSA_NAME_VERSION (vuseb);

  return sn;
}