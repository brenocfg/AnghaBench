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
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {int alloc; scalar_t__ n; char* z; } ;
typedef  TYPE_1__ SString ;
typedef  char* LPVOID ;
typedef  int /*<<< orphan*/  LPTSTR ;

/* Variables and functions */
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 int /*<<< orphan*/  FormatMessage (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MIN_ALLOC_SIZE ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 scalar_t__ TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* realloc (char*,scalar_t__) ; 
 int /*<<< orphan*/  strerror_r (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tListLen (char*) ; 
 int /*<<< orphan*/  tscTrace (char*,char*) ; 

int32_t SStringEnsureRemain(SString* pStr, int32_t size) {
  if (pStr->alloc - pStr->n > size) {
    return TSDB_CODE_SUCCESS;
  }

  // remain space is insufficient, allocate more spaces
  int32_t inc = (size < MIN_ALLOC_SIZE) ? size : MIN_ALLOC_SIZE;
  if (inc < (pStr->alloc >> 1)) {
    inc = (pStr->alloc >> 1);
  }

  // get the new size
  int32_t newsize = pStr->alloc + inc;

  char* tmp = realloc(pStr->z, newsize);
  if (tmp == NULL) {
#ifdef WINDOWS
    LPVOID lpMsgBuf;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
                  GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),  // Default language
                  (LPTSTR)&lpMsgBuf, 0, NULL);
    tscTrace("failed to allocate memory, reason:%s", lpMsgBuf);
    LocalFree(lpMsgBuf);
#else
    char errmsg[256] = {0};
    strerror_r(errno, errmsg, tListLen(errmsg));
    tscTrace("failed to allocate memory, reason:%s", errmsg);
#endif

    return TSDB_CODE_CLI_OUT_OF_MEMORY;
  }

  memset(tmp + pStr->n, 0, inc);
  pStr->z = tmp;

  return TSDB_CODE_SUCCESS;
}