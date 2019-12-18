#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_9__ {int /*<<< orphan*/  type; int /*<<< orphan*/  n; int /*<<< orphan*/  z; } ;
struct TYPE_8__ {int type; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_1__ SSchema ;
typedef  TYPE_2__ SSQLToken ;

/* Variables and functions */
 double DBL_MAX ; 
 scalar_t__ ERANGE ; 
 float FLT_MAX ; 
 double HUGE_VAL ; 
 int /*<<< orphan*/  INT16_MAX ; 
 int /*<<< orphan*/  INT16_MIN ; 
 int /*<<< orphan*/  INT32_MAX ; 
 int /*<<< orphan*/  INT32_MIN ; 
 int /*<<< orphan*/  INT64_MAX ; 
 int /*<<< orphan*/  INT64_MIN ; 
 int /*<<< orphan*/  INT8_MAX ; 
 int /*<<< orphan*/  INT8_MIN ; 
 int /*<<< orphan*/  INVALID_SQL_RET_MSG (char*,char*) ; 
 int /*<<< orphan*/  TK_BOOL ; 
 int /*<<< orphan*/  TK_FLOAT ; 
 int /*<<< orphan*/  TK_ILLEGAL ; 
 int /*<<< orphan*/  TK_INTEGER ; 
 int /*<<< orphan*/  TK_NULL ; 
 int /*<<< orphan*/  TK_STRING ; 
 int /*<<< orphan*/  TSDB_CODE_INVALID_SQL ; 
 int /*<<< orphan*/  TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  TSDB_DATA_BIGINT_NULL ; 
 char TSDB_DATA_BINARY_NULL ; 
 int /*<<< orphan*/  TSDB_DATA_BOOL_NULL ; 
 int /*<<< orphan*/  TSDB_DATA_DOUBLE_NULL ; 
 int /*<<< orphan*/  TSDB_DATA_FLOAT_NULL ; 
 int /*<<< orphan*/  TSDB_DATA_INT_NULL ; 
 int /*<<< orphan*/  TSDB_DATA_NCHAR_NULL ; 
 int /*<<< orphan*/  TSDB_DATA_NULL_STR_L ; 
 int /*<<< orphan*/  TSDB_DATA_SMALLINT_NULL ; 
 int /*<<< orphan*/  TSDB_DATA_TINYINT_NULL ; 
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
 int /*<<< orphan*/  TSDB_FALSE ; 
 int /*<<< orphan*/  TSDB_TRUE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  isinf (double) ; 
 int /*<<< orphan*/  isnan (double) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double strtod (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strtoll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taosMbsToUcs4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsParseTime (TYPE_2__*,int /*<<< orphan*/ *,char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscToDouble (TYPE_2__*,double*,char**) ; 
 int /*<<< orphan*/  tscToInteger (TYPE_2__*,int /*<<< orphan*/ *,char**) ; 

int32_t tsParseOneColumnData(SSchema *pSchema, SSQLToken *pToken, char *payload, char *msg, char **str, bool primaryKey,
                             int16_t timePrec) {
  int64_t iv;
  int32_t numType;
  char *  endptr = NULL;
  errno = 0;  // reset global error code

  switch (pSchema->type) {
    case TSDB_DATA_TYPE_BOOL: {  // bool
      if ((pToken->type == TK_BOOL || pToken->type == TK_STRING) && (pToken->n != 0)) {
        if (strncmp(pToken->z, "true", pToken->n) == 0) {
          *(uint8_t *)payload = TSDB_TRUE;
        } else if (strncmp(pToken->z, "false", pToken->n) == 0) {
          *(uint8_t *)payload = TSDB_FALSE;
        } else if (strncasecmp(TSDB_DATA_NULL_STR_L, pToken->z, pToken->n) == 0) {
          *(uint8_t *)payload = TSDB_DATA_BOOL_NULL;
        } else {
          INVALID_SQL_RET_MSG(msg, "data is illegal");
        }
      } else if (pToken->type == TK_INTEGER) {
        iv = strtoll(pToken->z, NULL, 10);
        *(uint8_t *)payload = (int8_t)((iv == 0) ? TSDB_FALSE : TSDB_TRUE);
      } else if (pToken->type == TK_FLOAT) {
        double dv = strtod(pToken->z, NULL);
        *(uint8_t *)payload = (int8_t)((dv == 0) ? TSDB_FALSE : TSDB_TRUE);
      } else if (pToken->type == TK_NULL) {
        *(uint8_t *)payload = TSDB_DATA_BOOL_NULL;
      } else {
        INVALID_SQL_RET_MSG(msg, "data is illegal");
      }
      break;
    }
    case TSDB_DATA_TYPE_TINYINT:
      if (pToken->type == TK_NULL) {
        *((int8_t *)payload) = TSDB_DATA_TINYINT_NULL;
      } else if ((pToken->type == TK_STRING) && (pToken->n != 0) &&
                 (strncasecmp(TSDB_DATA_NULL_STR_L, pToken->z, pToken->n) == 0)) {
        *((int8_t *)payload) = TSDB_DATA_TINYINT_NULL;
      } else {
        numType = tscToInteger(pToken, &iv, &endptr);
        if (errno == ERANGE || iv > INT8_MAX || iv <= INT8_MIN) {
          INVALID_SQL_RET_MSG(msg, "data is overflow");
        } else if (TK_ILLEGAL == numType) {
          INVALID_SQL_RET_MSG(msg, "data is illegal");
        }

        *((int8_t *)payload) = (int8_t)iv;
      }

      break;

    case TSDB_DATA_TYPE_SMALLINT:
      if (pToken->type == TK_NULL) {
        *((int16_t *)payload) = TSDB_DATA_SMALLINT_NULL;
      } else if ((pToken->type == TK_STRING) && (pToken->n != 0) &&
                 (strncasecmp(TSDB_DATA_NULL_STR_L, pToken->z, pToken->n) == 0)) {
        *((int16_t *)payload) = TSDB_DATA_SMALLINT_NULL;
      } else {
        numType = tscToInteger(pToken, &iv, &endptr);
        if (errno == ERANGE || iv > INT16_MAX || iv <= INT16_MIN) {
          INVALID_SQL_RET_MSG(msg, "data is overflow");
        } else if (TK_ILLEGAL == numType) {
          INVALID_SQL_RET_MSG(msg, "data is illegal");
        }

        *((int16_t *)payload) = (int16_t)iv;
      }
      break;

    case TSDB_DATA_TYPE_INT:
      if (pToken->type == TK_NULL) {
        *((int32_t *)payload) = TSDB_DATA_INT_NULL;
      } else if ((pToken->type == TK_STRING) && (pToken->n != 0) &&
                 (strncasecmp(TSDB_DATA_NULL_STR_L, pToken->z, pToken->n) == 0)) {
        *((int32_t *)payload) = TSDB_DATA_INT_NULL;
      } else {
        numType = tscToInteger(pToken, &iv, &endptr);
        if (errno == ERANGE || iv > INT32_MAX || iv <= INT32_MIN) {
          INVALID_SQL_RET_MSG(msg, "data is overflow");
        } else if (TK_ILLEGAL == numType) {
          INVALID_SQL_RET_MSG(msg, "data is illegal");
        }

        *((int32_t *)payload) = (int32_t)iv;
      }

      break;

    case TSDB_DATA_TYPE_BIGINT:
      if (pToken->type == TK_NULL) {
        *((int64_t *)payload) = TSDB_DATA_BIGINT_NULL;
      } else if ((pToken->type == TK_STRING) && (pToken->n != 0) &&
                 (strncasecmp(TSDB_DATA_NULL_STR_L, pToken->z, pToken->n) == 0)) {
        *((int64_t *)payload) = TSDB_DATA_BIGINT_NULL;
      } else {
        numType = tscToInteger(pToken, &iv, &endptr);
        if (errno == ERANGE || iv > INT64_MAX || iv <= INT64_MIN) {
          INVALID_SQL_RET_MSG(msg, "data is overflow");
        } else if (TK_ILLEGAL == numType) {
          INVALID_SQL_RET_MSG(msg, "data is illegal");
        }

        *((int64_t *)payload) = iv;
      }
      break;

    case TSDB_DATA_TYPE_FLOAT:
      if (pToken->type == TK_NULL) {
        *((int32_t *)payload) = TSDB_DATA_FLOAT_NULL;
      } else if ((pToken->type == TK_STRING) && (pToken->n != 0) &&
                 (strncasecmp(TSDB_DATA_NULL_STR_L, pToken->z, pToken->n) == 0)) {
        *((int32_t *)payload) = TSDB_DATA_FLOAT_NULL;
      } else {
        double dv;
        if (TK_ILLEGAL == tscToDouble(pToken, &dv, &endptr)) {
          INVALID_SQL_RET_MSG(msg, "data is illegal");
        }

        float fv = (float)dv;
        if (((dv == HUGE_VAL || dv == -HUGE_VAL) && errno == ERANGE) || (fv > FLT_MAX || fv < -FLT_MAX)) {
          INVALID_SQL_RET_MSG(msg, "data is illegal");
        }

        if (isinf(fv) || isnan(fv)) {
          *((int32_t *)payload) = TSDB_DATA_FLOAT_NULL;
        }

        *((float *)payload) = fv;
      }
      break;

    case TSDB_DATA_TYPE_DOUBLE:
      if (pToken->type == TK_NULL) {
        *((int64_t *)payload) = TSDB_DATA_DOUBLE_NULL;
      } else if ((pToken->type == TK_STRING) && (pToken->n != 0) &&
                 (strncasecmp(TSDB_DATA_NULL_STR_L, pToken->z, pToken->n) == 0)) {
        *((int64_t *)payload) = TSDB_DATA_DOUBLE_NULL;
      } else {
        double dv;
        if (TK_ILLEGAL == tscToDouble(pToken, &dv, &endptr)) {
          INVALID_SQL_RET_MSG(msg, "data is illegal");
        }

        if (((dv == HUGE_VAL || dv == -HUGE_VAL) && errno == ERANGE) || (dv > DBL_MAX || dv < -DBL_MAX)) {
          INVALID_SQL_RET_MSG(msg, "data is illegal");
        }

        if (isinf(dv) || isnan(dv)) {
          *((int64_t *)payload) = TSDB_DATA_DOUBLE_NULL;
        } else {
          *((double *)payload) = dv;
        }
      }
      break;

    case TSDB_DATA_TYPE_BINARY:
      // binary data cannot be null-terminated char string, otherwise the last char of the string is lost
      if (pToken->type == TK_NULL) {
        *payload = TSDB_DATA_BINARY_NULL;
      } else {
        // too long values will return invalid sql, not be truncated automatically
        if (pToken->n > pSchema->bytes) {
          INVALID_SQL_RET_MSG(msg, "value too long");
        }
        strncpy(payload, pToken->z, pToken->n);
      }

      break;

    case TSDB_DATA_TYPE_NCHAR:
      if (pToken->type == TK_NULL) {
        *(uint32_t *)payload = TSDB_DATA_NCHAR_NULL;
      } else {
        // if the converted output len is over than pSchema->bytes, return error: 'Argument list too long'
        if (!taosMbsToUcs4(pToken->z, pToken->n, payload, pSchema->bytes)) {
          sprintf(msg, "%s", strerror(errno));
          return TSDB_CODE_INVALID_SQL;
        }
      }
      break;

    case TSDB_DATA_TYPE_TIMESTAMP: {
      if (pToken->type == TK_NULL) {
        if (primaryKey) {
          *((int64_t *)payload) = 0;
        } else {
          *((int64_t *)payload) = TSDB_DATA_BIGINT_NULL;
        }
      } else {
        int64_t temp;
        if (tsParseTime(pToken, &temp, str, msg, timePrec) != TSDB_CODE_SUCCESS) {
          return TSDB_CODE_INVALID_SQL;
        }
        *((int64_t *)payload) = temp;
      }

      break;
    }
  }

  return 0;
}