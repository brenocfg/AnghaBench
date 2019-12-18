#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_8__ {int nType; int i64Key; float dKey; char* pz; void* nLen; } ;
typedef  TYPE_1__ tVariant ;
typedef  int int8_t ;
typedef  int int64_t ;
typedef  void* int32_t ;
typedef  int int16_t ;
struct TYPE_11__ {scalar_t__ numParams; TYPE_1__* params; } ;
struct TYPE_10__ {TYPE_4__ normal; } ;
struct TYPE_9__ {int buffer_type; size_t* length; scalar_t__ buffer; scalar_t__* is_null; } ;
typedef  TYPE_2__ TAOS_BIND ;
typedef  TYPE_3__ STscStmt ;
typedef  TYPE_4__ SNormalStmt ;

/* Variables and functions */
 int TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 int TSDB_CODE_INVALID_VALUE ; 
 int TSDB_CODE_SUCCESS ; 
#define  TSDB_DATA_TYPE_BIGINT 138 
#define  TSDB_DATA_TYPE_BINARY 137 
#define  TSDB_DATA_TYPE_BOOL 136 
#define  TSDB_DATA_TYPE_DOUBLE 135 
#define  TSDB_DATA_TYPE_FLOAT 134 
#define  TSDB_DATA_TYPE_INT 133 
#define  TSDB_DATA_TYPE_NCHAR 132 
#define  TSDB_DATA_TYPE_NULL 131 
#define  TSDB_DATA_TYPE_SMALLINT 130 
#define  TSDB_DATA_TYPE_TIMESTAMP 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  tVariantDestroy (TYPE_1__*) ; 
 int /*<<< orphan*/  tscTrace (char*,scalar_t__) ; 

__attribute__((used)) static int normalStmtBindParam(STscStmt* stmt, TAOS_BIND* bind) {
  SNormalStmt* normal = &stmt->normal;

  for (uint16_t i = 0; i < normal->numParams; ++i) {
    TAOS_BIND* tb = bind + i;
    tVariant* var = normal->params + i;
    tVariantDestroy(var);

    var->nLen = 0;
    if (tb->is_null != NULL && *(tb->is_null)) {
      var->nType = TSDB_DATA_TYPE_NULL;
      var->i64Key = 0;
      continue;
    }

    var->nType = tb->buffer_type;
    switch (tb->buffer_type) {
      case TSDB_DATA_TYPE_NULL:
        var->i64Key = 0;
        break;

      case TSDB_DATA_TYPE_BOOL:
        var->i64Key = (*(int8_t*)tb->buffer) ? 1 : 0;
        break;

      case TSDB_DATA_TYPE_TINYINT:
        var->i64Key = *(int8_t*)tb->buffer;
        break;

      case TSDB_DATA_TYPE_SMALLINT:
        var->i64Key = *(int16_t*)tb->buffer;
        break;

      case TSDB_DATA_TYPE_INT:
        var->i64Key = *(int32_t*)tb->buffer;
        break;

      case TSDB_DATA_TYPE_BIGINT:
      case TSDB_DATA_TYPE_TIMESTAMP:
        var->i64Key = *(int64_t*)tb->buffer;
        break;

      case TSDB_DATA_TYPE_FLOAT:
        var->dKey = *(float*)tb->buffer;
        break;

      case TSDB_DATA_TYPE_DOUBLE:
        var->dKey = *(double*)tb->buffer;
        break;

      case TSDB_DATA_TYPE_BINARY:
      case TSDB_DATA_TYPE_NCHAR:
        var->pz = (char*)malloc((*tb->length) + 1);
        if (var->pz == NULL) {
          return TSDB_CODE_CLI_OUT_OF_MEMORY;
        }
        memcpy(var->pz, tb->buffer, (*tb->length));
        var->pz[*tb->length] = 0;
        var->nLen = (int32_t)(*tb->length);
        break;

      default:
        tscTrace("param %d: type mismatch or invalid", i);
        return TSDB_CODE_INVALID_VALUE;
    }
  }
  
  return TSDB_CODE_SUCCESS;
}