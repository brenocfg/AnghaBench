#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int64_t ;
typedef  int int32_t ;

/* Variables and functions */
#define  TSDB_DATA_TYPE_BIGINT 134 
#define  TSDB_DATA_TYPE_BINARY 133 
#define  TSDB_DATA_TYPE_BOOL 132 
#define  TSDB_DATA_TYPE_DOUBLE 131 
#define  TSDB_DATA_TYPE_FLOAT 130 
#define  TSDB_DATA_TYPE_NCHAR 129 
#define  TSDB_DATA_TYPE_TIMESTAMP 128 
 int sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 

__attribute__((used)) static int32_t getToStringLength(char *pData, int32_t length, int32_t type) {
  char buf[512] = {0};

  int32_t len = 0;
  int32_t MAX_BOOL_TYPE_LENGTH = 5;  // max(strlen("true"), strlen("false"));
  switch (type) {
    case TSDB_DATA_TYPE_BINARY:
      return length;
    case TSDB_DATA_TYPE_NCHAR:
      return length;
    case TSDB_DATA_TYPE_DOUBLE: {
#ifdef _TD_ARM_32_
      double dv = 0;
      *(int64_t*)(&dv) = *(int64_t*)pData;
      len = sprintf(buf, "%f", dv);
#else
      len = sprintf(buf, "%lf", *(double *)pData);
#endif
      if (strncasecmp("nan", buf, 3) == 0) {
        len = 4;
      }
    }
      break;
    case TSDB_DATA_TYPE_FLOAT: {
#ifdef _TD_ARM_32_
      float fv = 0;
      *(int32_t*)(&fv) = *(int32_t*)pData;
      len = sprintf(buf, "%f", fv);
#else
      len = sprintf(buf, "%f", *(float *)pData);
#endif
      if (strncasecmp("nan", buf, 3) == 0) {
        len = 4;
      }
    }
      break;
    case TSDB_DATA_TYPE_TIMESTAMP:
    case TSDB_DATA_TYPE_BIGINT:
      len = sprintf(buf, "%lld", *(int64_t *)pData);
      break;
    case TSDB_DATA_TYPE_BOOL:
      len = MAX_BOOL_TYPE_LENGTH;
      break;
    default:
      len = sprintf(buf, "%d", *(int32_t *)pData);
      break;
  };
  return len;
}