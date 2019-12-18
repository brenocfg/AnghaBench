#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* payload; int allocSize; } ;
typedef  TYPE_1__ SSqlCmd ;

/* Variables and functions */
 int TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* realloc (char*,int) ; 

int tscAllocPayload(SSqlCmd* pCmd, int size) {
  assert(size > 0);

  if (pCmd->payload == NULL) {
    assert(pCmd->allocSize == 0);

    pCmd->payload = (char*)malloc(size);
    if (pCmd->payload == NULL) return TSDB_CODE_CLI_OUT_OF_MEMORY;
    pCmd->allocSize = size;
  } else {
    if (pCmd->allocSize < size) {
      char* b = realloc(pCmd->payload, size);
      if (b == NULL) return TSDB_CODE_CLI_OUT_OF_MEMORY;
      pCmd->payload = b;
      pCmd->allocSize = size;
    }
  }

  memset(pCmd->payload, 0, pCmd->allocSize);
  assert(pCmd->allocSize >= size);

  return TSDB_CODE_SUCCESS;
}