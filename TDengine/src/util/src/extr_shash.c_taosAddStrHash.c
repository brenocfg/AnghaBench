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
struct TYPE_2__ {int /*<<< orphan*/  dataSize; } ;
typedef  TYPE_1__ SHashObj ;

/* Variables and functions */
 void* taosAddStrHashWithSize (void*,char*,char*,int /*<<< orphan*/ ) ; 

void *taosAddStrHash(void *handle, char *string, char *pData) {
  if (string == NULL || string[0] == 0) return NULL;

  SHashObj *pObj = (SHashObj *)handle;
  return taosAddStrHashWithSize(handle, string, pData, pObj->dataSize);
}