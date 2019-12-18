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
struct TYPE_6__ {int type; int offset; scalar_t__ bytes; } ;
struct TYPE_5__ {int buffer_type; int /*<<< orphan*/  buffer; scalar_t__* length; scalar_t__* is_null; } ;
typedef  TYPE_1__ TAOS_BIND ;
typedef  TYPE_2__ SParamInfo ;

/* Variables and functions */
 int TSDB_CODE_INVALID_VALUE ; 
 int TSDB_CODE_SUCCESS ; 
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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,short) ; 
 int /*<<< orphan*/  setNull (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  taosMbsToUcs4 (int /*<<< orphan*/ ,scalar_t__,char*,scalar_t__) ; 

__attribute__((used)) static int doBindParam(char* data, SParamInfo* param, TAOS_BIND* bind) {
  if (bind->is_null != NULL && *(bind->is_null)) {
    setNull(data, param->type, param->bytes);
    return TSDB_CODE_SUCCESS;
  }

  if (bind->buffer_type != param->type) {
    return TSDB_CODE_INVALID_VALUE;
  }

  short size = 0;
  switch(param->type) {
    case TSDB_DATA_TYPE_BOOL:
    case TSDB_DATA_TYPE_TINYINT:
      size = 1;
      break;

    case TSDB_DATA_TYPE_SMALLINT:
      size = 2;
      break;

    case TSDB_DATA_TYPE_INT:
    case TSDB_DATA_TYPE_FLOAT:
      size = 4;
      break;

    case TSDB_DATA_TYPE_BIGINT:
    case TSDB_DATA_TYPE_DOUBLE:
    case TSDB_DATA_TYPE_TIMESTAMP:
      size = 8;
      break;

    case TSDB_DATA_TYPE_BINARY:
      if ((*bind->length) > param->bytes) {
        return TSDB_CODE_INVALID_VALUE;
      }
      size = (short)*bind->length;
      break;
    
    case TSDB_DATA_TYPE_NCHAR:
      if (!taosMbsToUcs4(bind->buffer, *bind->length, data + param->offset, param->bytes)) {
        return TSDB_CODE_INVALID_VALUE;
      }
      return TSDB_CODE_SUCCESS;

    default:
      assert(false);
      return TSDB_CODE_INVALID_VALUE;
  }

  memcpy(data + param->offset, bind->buffer, size);
  return TSDB_CODE_SUCCESS;
}