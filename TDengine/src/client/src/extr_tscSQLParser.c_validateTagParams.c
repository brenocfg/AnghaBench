#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nField; TYPE_1__* p; } ;
typedef  TYPE_2__ tFieldList ;
typedef  size_t int32_t ;
struct TYPE_6__ {size_t bytes; scalar_t__ type; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  SSqlCmd ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_DATA_TYPE_BINARY ; 
 scalar_t__ TSDB_DATA_TYPE_BOOL ; 
 scalar_t__ TSDB_DATA_TYPE_NCHAR ; 
 scalar_t__ TSDB_DATA_TYPE_TIMESTAMP ; 
 int TSDB_MAX_TAGS ; 
 size_t TSDB_MAX_TAGS_LEN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int has (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setErrMsg (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ validateColumnName (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool validateTagParams(tFieldList* pTagsList, tFieldList* pFieldList, SSqlCmd* pCmd) {
  assert(pTagsList != NULL);

  const char* msg1 = "invalid number of tag columns";
  const char* msg2 = "tag length too long";
  const char* msg3 = "duplicated column names";
  const char* msg4 = "timestamp not allowed in tags";
  const char* msg5 = "invalid data type in tags";
  const char* msg6 = "invalid tag name";
  const char* msg7 = "invalid binary/nchar tag length";

  // number of fields at least 1
  if (pTagsList->nField < 1 || pTagsList->nField > TSDB_MAX_TAGS) {
    setErrMsg(pCmd, msg1);
    return false;
  }

  int32_t nLen = 0;
  for (int32_t i = 0; i < pTagsList->nField; ++i) {
    nLen += pTagsList->p[i].bytes;
  }

  // max tag row length must be less than TSDB_MAX_TAGS_LEN
  if (nLen > TSDB_MAX_TAGS_LEN) {
    setErrMsg(pCmd, msg2);
    return false;
  }

  // field name must be unique
  for (int32_t i = 0; i < pTagsList->nField; ++i) {
    if (has(pFieldList, 0, pTagsList->p[i].name) == true) {
      setErrMsg(pCmd, msg3);
      return false;
    }
  }

  /* timestamp in tag is not allowed */
  for (int32_t i = 0; i < pTagsList->nField; ++i) {
    if (pTagsList->p[i].type == TSDB_DATA_TYPE_TIMESTAMP) {
      setErrMsg(pCmd, msg4);
      return false;
    }

    if (pTagsList->p[i].type < TSDB_DATA_TYPE_BOOL || pTagsList->p[i].type > TSDB_DATA_TYPE_NCHAR) {
      setErrMsg(pCmd, msg5);
      return false;
    }

    if ((pTagsList->p[i].type == TSDB_DATA_TYPE_BINARY && pTagsList->p[i].bytes <= 0) ||
        (pTagsList->p[i].type == TSDB_DATA_TYPE_NCHAR && pTagsList->p[i].bytes <= 0)) {
      setErrMsg(pCmd, msg7);
      return false;
    }

    if (validateColumnName(pTagsList->p[i].name) != TSDB_CODE_SUCCESS) {
      setErrMsg(pCmd, msg6);
      return false;
    }

    if (has(pTagsList, i + 1, pTagsList->p[i].name) == true) {
      setErrMsg(pCmd, msg3);
      return false;
    }
  }

  return true;
}