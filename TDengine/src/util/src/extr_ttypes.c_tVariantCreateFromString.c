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
typedef  int uint32_t ;
struct TYPE_3__ {int nType; int /*<<< orphan*/  pz; int /*<<< orphan*/  nLen; int /*<<< orphan*/  dKey; int /*<<< orphan*/  i64Key; } ;
typedef  TYPE_1__ tVariant ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
#define  TSDB_DATA_TYPE_BIGINT 135 
#define  TSDB_DATA_TYPE_BINARY 134 
#define  TSDB_DATA_TYPE_BOOL 133 
#define  TSDB_DATA_TYPE_DOUBLE 132 
#define  TSDB_DATA_TYPE_FLOAT 131 
#define  TSDB_DATA_TYPE_INT 130 
 int TSDB_DATA_TYPE_NULL ; 
#define  TSDB_DATA_TYPE_SMALLINT 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 int /*<<< orphan*/  TSDB_FALSE ; 
 int /*<<< orphan*/  TSDB_TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  strdequote (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  strndup (char*,int) ; 
 int /*<<< orphan*/  strtod (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strtoll (char*,int /*<<< orphan*/ *,int) ; 

void tVariantCreateFromString(tVariant *pVar, char *pz, uint32_t len, uint32_t type) {
  switch (type) {
    case TSDB_DATA_TYPE_BOOL: {
      int32_t k = strncasecmp(pz, "true", 4);
      if (k == 0) {
        pVar->i64Key = TSDB_TRUE;
      } else {
        assert(strncasecmp(pz, "false", 5) == 0);
        pVar->i64Key = TSDB_FALSE;
      }
      break;
    }
    case TSDB_DATA_TYPE_TINYINT:
    case TSDB_DATA_TYPE_SMALLINT:
    case TSDB_DATA_TYPE_BIGINT:
    case TSDB_DATA_TYPE_INT:
      pVar->i64Key = strtoll(pz, NULL, 10);
      break;
    case TSDB_DATA_TYPE_DOUBLE:
    case TSDB_DATA_TYPE_FLOAT:
      pVar->dKey = strtod(pz, NULL);
      break;
    case TSDB_DATA_TYPE_BINARY: {
      pVar->pz = strndup(pz, len);
      pVar->nLen = strdequote(pVar->pz);
      break;
    }

    default: {  // nType == 0 means the null value
      type = TSDB_DATA_TYPE_NULL;
    }
  }

  pVar->nType = type;
}