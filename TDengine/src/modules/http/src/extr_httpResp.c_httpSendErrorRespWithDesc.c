#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ipstr; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ HttpContext ;

/* Variables and functions */
#define  HTTP_GC_QUERY_NULL 184 
#define  HTTP_GC_QUERY_SIZE 183 
#define  HTTP_GEN_TAOSD_TOKEN_ERR 182 
#define  HTTP_INVALID_AUTH_TOKEN 181 
#define  HTTP_INVALID_BASIC_AUTH_TOKEN 180 
#define  HTTP_INVALID_DB_TABLE 179 
#define  HTTP_INVALID_MULTI_REQUEST 178 
#define  HTTP_INVALID_TAOSD_AUTH_TOKEN 177 
#define  HTTP_NO_ENOUGH_MEMORY 176 
#define  HTTP_NO_ENOUGH_SESSIONS 175 
#define  HTTP_NO_EXEC_USEDB 174 
#define  HTTP_NO_MSG_INPUT 173 
#define  HTTP_NO_SQL_INPUT 172 
#define  HTTP_PARSE_BODY_ERROR 171 
#define  HTTP_PARSE_CHUNKED_BODY_ERROR 170 
#define  HTTP_PARSE_GC_REQ_ERROR 169 
#define  HTTP_PARSE_HEAD_ERROR 168 
#define  HTTP_PARSE_HTTP_METHOD_ERROR 167 
#define  HTTP_PARSE_HTTP_VERSION_ERROR 166 
#define  HTTP_PARSE_URL_ERROR 165 
#define  HTTP_PARSE_USR_ERROR 164 
#define  HTTP_REQUSET_TOO_BIG 163 
#define  HTTP_SERVER_OFFLINE 162 
#define  HTTP_SESSION_FULL 161 
#define  HTTP_SUCCESS 160 
#define  HTTP_TG_DB_NOT_INPUT 159 
#define  HTTP_TG_DB_TOO_LONG 158 
#define  HTTP_TG_FIELDS_NULL 157 
#define  HTTP_TG_FIELDS_SIZE_0 156 
#define  HTTP_TG_FIELDS_SIZE_LONG 155 
#define  HTTP_TG_FIELD_NAME_NULL 154 
#define  HTTP_TG_FIELD_NAME_SIZE 153 
#define  HTTP_TG_FIELD_NULL 152 
#define  HTTP_TG_FIELD_VALUE_NULL 151 
#define  HTTP_TG_FIELD_VALUE_TYPE 150 
#define  HTTP_TG_HOST_NOT_STRING 149 
#define  HTTP_TG_INVALID_JSON 148 
#define  HTTP_TG_METRICS_NULL 147 
#define  HTTP_TG_METRICS_SIZE 146 
#define  HTTP_TG_METRIC_NAME_LONG 145 
#define  HTTP_TG_METRIC_NAME_NULL 144 
#define  HTTP_TG_METRIC_NULL 143 
#define  HTTP_TG_METRIC_TYPE 142 
#define  HTTP_TG_TABLE_NULL 141 
#define  HTTP_TG_TABLE_SIZE 140 
#define  HTTP_TG_TAGS_NULL 139 
#define  HTTP_TG_TAGS_SIZE_0 138 
#define  HTTP_TG_TAGS_SIZE_LONG 137 
#define  HTTP_TG_TAG_NAME_NULL 136 
#define  HTTP_TG_TAG_NAME_SIZE 135 
#define  HTTP_TG_TAG_NULL 134 
#define  HTTP_TG_TAG_VALUE_NULL 133 
#define  HTTP_TG_TAG_VALUE_TYPE 132 
#define  HTTP_TG_TIMESTAMP_NULL 131 
#define  HTTP_TG_TIMESTAMP_TYPE 130 
#define  HTTP_TG_TIMESTAMP_VAL_NULL 129 
#define  HTTP_UNSUPPORT_URL 128 
 int /*<<< orphan*/  httpError (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char** httpMsg ; 
 int /*<<< orphan*/  httpSendErrorRespImp (TYPE_1__*,int,char*,int,char*) ; 

void httpSendErrorRespWithDesc(HttpContext *pContext, int errNo, char *desc) {
  int   httpCode = 500;
  char *httpCodeStr = "Internal Server Error";
  switch (errNo) {
    case HTTP_SUCCESS:
      httpCode = 200;
      httpCodeStr = "OK";
      break;
    case HTTP_SERVER_OFFLINE:
    case HTTP_UNSUPPORT_URL:
      httpCode = 404;
      httpCodeStr = "Not Found";
      break;
    case HTTP_PARSE_HTTP_METHOD_ERROR:
      httpCode = 405;
      httpCodeStr = "Method Not Allowed";
      break;
    case HTTP_PARSE_HTTP_VERSION_ERROR:
      httpCode = 505;
      httpCodeStr = "HTTP Version Not Supported";
      break;
    case HTTP_PARSE_HEAD_ERROR:
      httpCode = 406;
      httpCodeStr = "Not Acceptable";
      break;
    case HTTP_REQUSET_TOO_BIG:
      httpCode = 413;
      httpCodeStr = "Request Entity Too Large";
      break;
    case HTTP_PARSE_BODY_ERROR:
    case HTTP_PARSE_CHUNKED_BODY_ERROR:
      httpCode = 409;
      httpCodeStr = "Conflict";
      break;
    case HTTP_PARSE_URL_ERROR:
      httpCode = 414;
      httpCodeStr = "Request-URI Invalid";
      break;
    case HTTP_INVALID_AUTH_TOKEN:
    case HTTP_PARSE_USR_ERROR:
      httpCode = 401;
      httpCodeStr = "Unauthorized";
      break;
    case HTTP_NO_SQL_INPUT:
      httpCode = 400;
      httpCodeStr = "Bad Request";
      break;
    case HTTP_SESSION_FULL:
      httpCode = 421;
      httpCodeStr = "Too many connections";
      break;
    case HTTP_NO_ENOUGH_MEMORY:
    case HTTP_GEN_TAOSD_TOKEN_ERR:
      httpCode = 507;
      httpCodeStr = "Insufficient Storage";
      break;
    case HTTP_INVALID_DB_TABLE:
    case HTTP_NO_EXEC_USEDB:
    case HTTP_PARSE_GC_REQ_ERROR:
    case HTTP_INVALID_MULTI_REQUEST:
    case HTTP_NO_MSG_INPUT:
      httpCode = 400;
      httpCodeStr = "Bad Request";
      break;
    case HTTP_NO_ENOUGH_SESSIONS:
      httpCode = 421;
      httpCodeStr = "Too many connections";
      break;
    // telegraf
    case HTTP_TG_DB_NOT_INPUT:
    case HTTP_TG_DB_TOO_LONG:
    case HTTP_TG_INVALID_JSON:
    case HTTP_TG_METRICS_NULL:
    case HTTP_TG_METRICS_SIZE:
    case HTTP_TG_METRIC_NULL:
    case HTTP_TG_METRIC_TYPE:
    case HTTP_TG_METRIC_NAME_NULL:
    case HTTP_TG_METRIC_NAME_LONG:
    case HTTP_TG_TIMESTAMP_NULL:
    case HTTP_TG_TIMESTAMP_TYPE:
    case HTTP_TG_TIMESTAMP_VAL_NULL:
    case HTTP_TG_TAGS_NULL:
    case HTTP_TG_TAGS_SIZE_0:
    case HTTP_TG_TAGS_SIZE_LONG:
    case HTTP_TG_TAG_NULL:
    case HTTP_TG_TAG_NAME_NULL:
    case HTTP_TG_TAG_NAME_SIZE:
    case HTTP_TG_TAG_VALUE_TYPE:
    case HTTP_TG_TAG_VALUE_NULL:
    case HTTP_TG_TABLE_NULL:
    case HTTP_TG_TABLE_SIZE:
    case HTTP_TG_FIELDS_NULL:
    case HTTP_TG_FIELDS_SIZE_0:
    case HTTP_TG_FIELDS_SIZE_LONG:
    case HTTP_TG_FIELD_NULL:
    case HTTP_TG_FIELD_NAME_NULL:
    case HTTP_TG_FIELD_NAME_SIZE:
    case HTTP_TG_FIELD_VALUE_TYPE:
    case HTTP_TG_FIELD_VALUE_NULL:
    case HTTP_INVALID_BASIC_AUTH_TOKEN:
    case HTTP_INVALID_TAOSD_AUTH_TOKEN:
    case HTTP_TG_HOST_NOT_STRING:
    // grafana
    case HTTP_GC_QUERY_NULL:
    case HTTP_GC_QUERY_SIZE:
      httpCode = 400;
      httpCodeStr = "Bad Request";
      break;
    default:
      httpError("context:%p, fd:%d, ip:%s, error:%d not recognized", pContext, pContext->fd, pContext->ipstr, errNo);
      break;
  }

  if (desc == NULL) {
    httpSendErrorRespImp(pContext, httpCode, httpCodeStr, errNo + 1000, httpMsg[errNo]);
  } else {
    httpSendErrorRespImp(pContext, httpCode, httpCodeStr, errNo + 1000, desc);
  }
}