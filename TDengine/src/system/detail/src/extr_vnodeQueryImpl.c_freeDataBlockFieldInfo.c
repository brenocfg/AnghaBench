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
struct TYPE_4__ {int /*<<< orphan*/  fields; } ;
struct TYPE_5__ {TYPE_1__ pBlock; } ;
typedef  TYPE_2__ SMeterDataBlockInfoEx ;

/* Variables and functions */
 int /*<<< orphan*/  tfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void freeDataBlockFieldInfo(SMeterDataBlockInfoEx *pDataBlockInfoEx, int32_t len) {
  for (int32_t i = 0; i < len; ++i) {
    tfree(pDataBlockInfoEx[i].pBlock.fields);
  }
}