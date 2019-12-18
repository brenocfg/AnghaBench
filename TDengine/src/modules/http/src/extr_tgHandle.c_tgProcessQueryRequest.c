#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cJSON ;
struct TYPE_14__ {char* pos; } ;
struct TYPE_17__ {TYPE_1__ data; } ;
struct TYPE_18__ {TYPE_2__* multiCmds; int /*<<< orphan*/ * encodeMethod; int /*<<< orphan*/  reqType; int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; TYPE_4__ parser; } ;
struct TYPE_16__ {void* sql; void* cmdReturnType; void* cmdType; } ;
struct TYPE_15__ {int pos; } ;
typedef  TYPE_3__ HttpSqlCmd ;
typedef  TYPE_4__ HttpParser ;
typedef  TYPE_5__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_BUFFER_SIZE ; 
 void* HTTP_CMD_RETURN_TYPE_NO_RETURN ; 
 void* HTTP_CMD_TYPE_CREATE_DB ; 
 int HTTP_MAX_CMD_SIZE ; 
 int /*<<< orphan*/  HTTP_NO_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  HTTP_NO_MSG_INPUT ; 
 int /*<<< orphan*/  HTTP_REQTYPE_MULTI_SQL ; 
 int /*<<< orphan*/  HTTP_TG_INVALID_JSON ; 
 int /*<<< orphan*/  HTTP_TG_METRICS_NULL ; 
 int /*<<< orphan*/  HTTP_TG_METRICS_SIZE ; 
 int /*<<< orphan*/  cJSON_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cJSON_GetArrayItem (int /*<<< orphan*/ *,int) ; 
 int cJSON_GetArraySize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cJSON_GetObjectItem (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * cJSON_Parse (char*) ; 
 void* httpAddToSqlCmdBuffer (TYPE_5__*,char*,char*) ; 
 int /*<<< orphan*/  httpMallocMultiCmds (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* httpNewSqlCmd (TYPE_5__*) ; 
 int /*<<< orphan*/  httpSendErrorResp (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpTrace (char*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  tgProcessSingleMetric (TYPE_5__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tgQueryMethod ; 

bool tgProcessQueryRequest(HttpContext *pContext, char *db) {
  httpTrace("context:%p, fd:%d, ip:%s, process telegraf query msg", pContext, pContext->fd, pContext->ipstr);

  HttpParser *pParser = &pContext->parser;
  char *      filter = pParser->data.pos;
  if (filter == NULL) {
    httpSendErrorResp(pContext, HTTP_NO_MSG_INPUT);
    return false;
  }

  cJSON *root = cJSON_Parse(filter);
  if (root == NULL) {
    httpSendErrorResp(pContext, HTTP_TG_INVALID_JSON);
    return false;
  }

  cJSON *metrics = cJSON_GetObjectItem(root, "metrics");
  if (metrics != NULL) {
    int size = cJSON_GetArraySize(metrics);
    httpTrace("context:%p, fd:%d, ip:%s, multiple metrics:%d at one time", pContext, pContext->fd, pContext->ipstr,
              size);
    if (size <= 0) {
      httpSendErrorResp(pContext, HTTP_TG_METRICS_NULL);
      cJSON_Delete(root);
      return false;
    }

    int cmdSize = size * 2 + 1;
    if (cmdSize > HTTP_MAX_CMD_SIZE) {
      httpSendErrorResp(pContext, HTTP_TG_METRICS_SIZE);
      cJSON_Delete(root);
      return false;
    }

    if (!httpMallocMultiCmds(pContext, cmdSize, HTTP_BUFFER_SIZE)) {
      httpSendErrorResp(pContext, HTTP_NO_ENOUGH_MEMORY);
      cJSON_Delete(root);
      return false;
    }

    HttpSqlCmd *cmd = httpNewSqlCmd(pContext);
    if (cmd == NULL) {
      httpSendErrorResp(pContext, HTTP_NO_ENOUGH_MEMORY);
      cJSON_Delete(root);
      return false;
    }
    cmd->cmdType = HTTP_CMD_TYPE_CREATE_DB;
    cmd->cmdReturnType = HTTP_CMD_RETURN_TYPE_NO_RETURN;
    cmd->sql = httpAddToSqlCmdBuffer(pContext, "create database if not exists %s", db);

    for (int i = 0; i < size; i++) {
      cJSON *metric = cJSON_GetArrayItem(metrics, i);
      if (metric != NULL) {
        if (!tgProcessSingleMetric(pContext, metric, db)) {
          cJSON_Delete(root);
          return false;
        }
      }
    }
  } else {
    httpTrace("context:%p, fd:%d, ip:%s, single metric", pContext, pContext->fd, pContext->ipstr);

    if (!httpMallocMultiCmds(pContext, 3, HTTP_BUFFER_SIZE)) {
      httpSendErrorResp(pContext, HTTP_NO_ENOUGH_MEMORY);
      cJSON_Delete(root);
      return false;
    }

    HttpSqlCmd *cmd = httpNewSqlCmd(pContext);
    if (cmd == NULL) {
      httpSendErrorResp(pContext, HTTP_NO_ENOUGH_MEMORY);
      cJSON_Delete(root);
      return false;
    }
    cmd->cmdType = HTTP_CMD_TYPE_CREATE_DB;
    cmd->cmdReturnType = HTTP_CMD_RETURN_TYPE_NO_RETURN;
    cmd->sql = httpAddToSqlCmdBuffer(pContext, "create database if not exists %s", db);

    if (!tgProcessSingleMetric(pContext, root, db)) {
      cJSON_Delete(root);
      return false;
    }
  }

  cJSON_Delete(root);

  pContext->reqType = HTTP_REQTYPE_MULTI_SQL;
  pContext->encodeMethod = &tgQueryMethod;
  pContext->multiCmds->pos = 2;

  return true;
}