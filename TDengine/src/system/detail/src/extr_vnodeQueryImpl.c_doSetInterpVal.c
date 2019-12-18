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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  size_t int32_t ;
typedef  int int16_t ;
struct TYPE_5__ {TYPE_1__* param; } ;
struct TYPE_4__ {char* pz; int nType; size_t nLen; } ;
typedef  int /*<<< orphan*/  TSKEY ;
typedef  TYPE_2__ SQLFunctionCtx ;

/* Variables and functions */
 double GET_DOUBLE_VAL (char*) ; 
 double GET_FLOAT_VAL (char*) ; 
 int /*<<< orphan*/  GET_INT64_VAL (char*) ; 
#define  TSDB_DATA_TYPE_BIGINT 137 
#define  TSDB_DATA_TYPE_BINARY 136 
#define  TSDB_DATA_TYPE_BOOL 135 
#define  TSDB_DATA_TYPE_DOUBLE 134 
#define  TSDB_DATA_TYPE_FLOAT 133 
#define  TSDB_DATA_TYPE_INT 132 
#define  TSDB_DATA_TYPE_NCHAR 131 
#define  TSDB_DATA_TYPE_SMALLINT 130 
#define  TSDB_DATA_TYPE_TIMESTAMP 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 size_t TSDB_KEYSIZE ; 
 size_t TSDB_NCHAR_SIZE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* calloc (int,size_t) ; 
 char* malloc (size_t) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 size_t wcslen (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wcsncpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void doSetInterpVal(SQLFunctionCtx *pCtx, TSKEY ts, int16_t type, int32_t index, char *data) {
  assert(pCtx->param[index].pz == NULL);

  int32_t len = 0;
  size_t  t = 0;

  if (type == TSDB_DATA_TYPE_BINARY) {
    t = strlen(data);

    len = t + 1 + TSDB_KEYSIZE;
    pCtx->param[index].pz = calloc(1, len);
  } else if (type == TSDB_DATA_TYPE_NCHAR) {
    t = wcslen((const wchar_t *)data);

    len = (t + 1) * TSDB_NCHAR_SIZE + TSDB_KEYSIZE;
    pCtx->param[index].pz = calloc(1, len);
  } else {
    len = TSDB_KEYSIZE * 2;
    pCtx->param[index].pz = malloc(len);
  }

  pCtx->param[index].nType = TSDB_DATA_TYPE_BINARY;

  char *z = pCtx->param[index].pz;
  *(TSKEY *)z = ts;
  z += TSDB_KEYSIZE;

  switch (type) {
    case TSDB_DATA_TYPE_FLOAT:
      *(double *)z = GET_FLOAT_VAL(data);
      break;
    case TSDB_DATA_TYPE_DOUBLE:
      *(double *)z = GET_DOUBLE_VAL(data);
      break;
    case TSDB_DATA_TYPE_INT:
    case TSDB_DATA_TYPE_BOOL:
    case TSDB_DATA_TYPE_BIGINT:
    case TSDB_DATA_TYPE_TINYINT:
    case TSDB_DATA_TYPE_SMALLINT:
    case TSDB_DATA_TYPE_TIMESTAMP:
      *(int64_t *)z = GET_INT64_VAL(data);
      break;
    case TSDB_DATA_TYPE_BINARY:
      strncpy(z, data, t);
      break;
    case TSDB_DATA_TYPE_NCHAR: {
      wcsncpy((wchar_t *)z, (const wchar_t *)data, t);
    } break;
    default:
      assert(0);
  }

  pCtx->param[index].nLen = len;
}