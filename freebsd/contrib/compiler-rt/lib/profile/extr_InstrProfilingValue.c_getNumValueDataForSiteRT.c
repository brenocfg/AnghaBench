#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_2__ {size_t** SiteCountArray; } ;
typedef  TYPE_1__ ValueProfRuntimeRecord ;

/* Variables and functions */

__attribute__((used)) static uint32_t getNumValueDataForSiteRT(const void *R, uint32_t VK,
                                         uint32_t S) {
  const ValueProfRuntimeRecord *Record = (const ValueProfRuntimeRecord *)R;
  return Record->SiteCountArray[VK][S];
}