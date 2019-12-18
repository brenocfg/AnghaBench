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
typedef  size_t int32_t ;
struct TYPE_4__ {size_t vnode; } ;
struct TYPE_5__ {TYPE_1__ info; } ;
typedef  TYPE_2__ STSVnodeBlockInfoEx ;

/* Variables and functions */

__attribute__((used)) static int32_t tsBufFindVnodeIndexFromId(STSVnodeBlockInfoEx* pVnodeInfoEx, int32_t numOfVnodes, int32_t vnodeId) {
  int32_t j = -1;
  for (int32_t i = 0; i < numOfVnodes; ++i) {
    if (pVnodeInfoEx[i].info.vnode == vnodeId) {
      j = i;
      break;
    }
  }

  return j;
}