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
typedef  int /*<<< orphan*/  tSkipListNode ;
struct TYPE_3__ {scalar_t__ nType; int nLen; } ;
typedef  TYPE_1__ tSkipListKey ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ TSDB_DATA_TYPE_BINARY ; 
 scalar_t__ TSDB_DATA_TYPE_NCHAR ; 
 int TSDB_NCHAR_SIZE ; 

__attribute__((used)) static size_t getOneNodeSize(const tSkipListKey *pKey, int32_t nLevel) {
  size_t size = sizeof(tSkipListNode) + sizeof(intptr_t) * (nLevel << 1);
  if (pKey->nType == TSDB_DATA_TYPE_BINARY) {
    size += pKey->nLen + 1;
  } else if (pKey->nType == TSDB_DATA_TYPE_NCHAR) {
    size += (pKey->nLen + 1) * TSDB_NCHAR_SIZE;
  }

  return size;
}