#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_4__ {char** offset; } ;
struct TYPE_3__ {char* data; } ;
typedef  TYPE_1__ SData ;
typedef  TYPE_2__ SCacheBlock ;

/* Variables and functions */

__attribute__((used)) static char *doGetDataBlockImpl(const char *sdata, int32_t colIdx, bool isDiskFileBlock) {
  if (isDiskFileBlock) {
    return ((SData **)sdata)[colIdx]->data;
  } else {
    return ((SCacheBlock *)sdata)->offset[colIdx];
  }
}