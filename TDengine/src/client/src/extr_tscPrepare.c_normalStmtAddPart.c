#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_6__ {int numParts; int sizeParts; int /*<<< orphan*/  numParams; TYPE_1__* parts; } ;
struct TYPE_5__ {int isParam; char* str; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ SNormalStmtPart ;
typedef  TYPE_2__ SNormalStmt ;

/* Variables and functions */
 int TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 int TSDB_CODE_SUCCESS ; 
 void* realloc (TYPE_1__*,int) ; 

__attribute__((used)) static int normalStmtAddPart(SNormalStmt* stmt, bool isParam, char* str, uint32_t len) {
  uint16_t size = stmt->numParts + 1;
  if (size > stmt->sizeParts) {
    size *= 2;
    void* tmp = realloc(stmt->parts, sizeof(SNormalStmtPart) * size);
    if (tmp == NULL) {
      return TSDB_CODE_CLI_OUT_OF_MEMORY;
    }
    stmt->sizeParts = size;
    stmt->parts = (SNormalStmtPart*)tmp;
  }

  stmt->parts[stmt->numParts].isParam = isParam;
  stmt->parts[stmt->numParts].str = str;
  stmt->parts[stmt->numParts].len = len;

  ++stmt->numParts;
  if (isParam) {
    ++stmt->numParams;
  }

  return TSDB_CODE_SUCCESS;
}