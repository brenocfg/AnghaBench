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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sdbEcommit ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ SSdbTable ;

/* Variables and functions */
 int /*<<< orphan*/  SDB_ENDCOMMIT ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void sdbFinishCommit(void *handle) {
  SSdbTable *pTable = (SSdbTable *)handle;
  uint32_t   sdbEcommit = SDB_ENDCOMMIT;

  off_t offset = lseek(pTable->fd, 0, SEEK_END);
  assert(offset == pTable->size);
  twrite(pTable->fd, &sdbEcommit, sizeof(sdbEcommit));
  pTable->size += sizeof(sdbEcommit);
}