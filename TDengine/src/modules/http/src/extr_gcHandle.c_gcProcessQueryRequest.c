#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {char* valuestring; } ;
typedef  TYPE_3__ cJSON ;
struct TYPE_23__ {char* pos; } ;
struct TYPE_27__ {TYPE_1__ data; } ;
struct TYPE_28__ {TYPE_2__* multiCmds; int /*<<< orphan*/ * encodeMethod; int /*<<< orphan*/  reqType; int /*<<< orphan*/  user; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_5__ parser; } ;
struct TYPE_26__ {int sql; int values; int table; int timestamp; scalar_t__ numOfRows; } ;
struct TYPE_24__ {scalar_t__ pos; } ;
typedef  TYPE_4__ HttpSqlCmd ;
typedef  TYPE_5__ HttpParser ;
typedef  TYPE_6__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_BUFFER_SIZE ; 
 int /*<<< orphan*/  HTTP_GC_QUERY_NULL ; 
 int /*<<< orphan*/  HTTP_GC_QUERY_SIZE ; 
 scalar_t__ HTTP_GC_TARGET_SIZE ; 
 int /*<<< orphan*/  HTTP_NO_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  HTTP_NO_MSG_INPUT ; 
 int /*<<< orphan*/  HTTP_PARSE_GC_REQ_ERROR ; 
 int /*<<< orphan*/  HTTP_REQTYPE_MULTI_SQL ; 
 int /*<<< orphan*/  cJSON_Delete (TYPE_3__*) ; 
 TYPE_3__* cJSON_GetArrayItem (TYPE_3__*,int) ; 
 int cJSON_GetArraySize (TYPE_3__*) ; 
 TYPE_3__* cJSON_GetObjectItem (TYPE_3__*,char*) ; 
 TYPE_3__* cJSON_Parse (char*) ; 
 int /*<<< orphan*/  gcQueryMethod ; 
 int httpAddToSqlCmdBuffer (TYPE_6__*,char*) ; 
 int httpAddToSqlCmdBufferWithSize (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  httpMallocMultiCmds (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* httpNewSqlCmd (TYPE_6__*) ; 
 int /*<<< orphan*/  httpSendErrorResp (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  httpWarn (char*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

bool gcProcessQueryRequest(HttpContext* pContext) {
  httpTrace("context:%p, fd:%d, ip:%s, process grafana query msg", pContext, pContext->fd, pContext->ipstr);

  HttpParser* pParser = &pContext->parser;
  char*       filter = pParser->data.pos;
  if (filter == NULL) {
    httpSendErrorResp(pContext, HTTP_NO_MSG_INPUT);
    return false;
  }

  cJSON* root = cJSON_Parse(filter);
  if (root == NULL) {
    httpSendErrorResp(pContext, HTTP_PARSE_GC_REQ_ERROR);
    return false;
  }

  int size = cJSON_GetArraySize(root);
  if (size <= 0) {
    httpSendErrorResp(pContext, HTTP_GC_QUERY_NULL);
    cJSON_Delete(root);
    return false;
  }

  if (size > 100) {
    httpSendErrorResp(pContext, HTTP_GC_QUERY_SIZE);
    cJSON_Delete(root);
    return false;
  }

  if (!httpMallocMultiCmds(pContext, size, HTTP_BUFFER_SIZE)) {
    httpSendErrorResp(pContext, HTTP_NO_ENOUGH_MEMORY);
    cJSON_Delete(root);
    return false;
  }

  for (int i = 0; i < size; ++i) {
    cJSON* query = cJSON_GetArrayItem(root, i);
    if (query == NULL) continue;

    cJSON* refId = cJSON_GetObjectItem(query, "refId");
    if (refId == NULL || refId->valuestring == NULL || strlen(refId->valuestring) == 0) {
      httpTrace("context:%p, fd:%d, ip:%s, user:%s, refId is null", pContext, pContext->fd, pContext->ipstr,
                pContext->user);
      continue;
    }

    int refIdBuffer = httpAddToSqlCmdBuffer(pContext, refId->valuestring);
    if (refIdBuffer == -1) {
      httpWarn("context:%p, fd:%d, ip:%s, user:%s, refId buffer is full", pContext, pContext->fd, pContext->ipstr,
               pContext->user);
      break;
    }

    cJSON* alias = cJSON_GetObjectItem(query, "alias");
    int    aliasBuffer = -1;
    if (!(alias == NULL || alias->valuestring == NULL || strlen(alias->valuestring) == 0)) {
      aliasBuffer = httpAddToSqlCmdBuffer(pContext, alias->valuestring);
      if (aliasBuffer == -1) {
        httpWarn("context:%p, fd:%d, ip:%s, user:%s, alias buffer is full", pContext, pContext->fd, pContext->ipstr,
                 pContext->user);
        break;
      }
    }
    if (aliasBuffer == -1) {
      aliasBuffer = httpAddToSqlCmdBuffer(pContext, "");
    }

    cJSON* sql = cJSON_GetObjectItem(query, "sql");
    if (sql == NULL || sql->valuestring == NULL || strlen(sql->valuestring) == 0) {
      httpTrace("context:%p, fd:%d, ip:%s, user:%s, sql is null", pContext, pContext->fd, pContext->ipstr,
                pContext->user);
      continue;
    }

    int sqlBuffer = httpAddToSqlCmdBuffer(pContext, sql->valuestring);
    if (sqlBuffer == -1) {
      httpWarn("context:%p, fd:%d, ip:%s, user:%s, sql buffer is full", pContext, pContext->fd, pContext->ipstr,
               pContext->user);
      break;
    }

    HttpSqlCmd* cmd = httpNewSqlCmd(pContext);
    if (cmd == NULL) {
      httpSendErrorResp(pContext, HTTP_NO_ENOUGH_MEMORY);
      cJSON_Delete(root);
      return false;
    }

    cmd->sql = sqlBuffer;
    cmd->values = refIdBuffer;
    cmd->table = aliasBuffer;
    cmd->numOfRows = 0;                                                                 // hack way as target flags
    cmd->timestamp = httpAddToSqlCmdBufferWithSize(pContext, HTTP_GC_TARGET_SIZE + 1);  // hack way

    if (cmd->timestamp == -1) {
      httpWarn("context:%p, fd:%d, ip:%s, user:%s, cant't malloc target size, sql buffer is full",
               pContext, pContext->fd, pContext->ipstr, pContext->user);
      break;
    }
  }

  pContext->reqType = HTTP_REQTYPE_MULTI_SQL;
  pContext->encodeMethod = &gcQueryMethod;
  pContext->multiCmds->pos = 0;

  return true;
}