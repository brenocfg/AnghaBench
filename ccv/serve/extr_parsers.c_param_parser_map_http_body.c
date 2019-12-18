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
typedef  int /*<<< orphan*/  string_type ;
typedef  int /*<<< orphan*/  size_type ;
typedef  int /*<<< orphan*/  point_type ;
struct TYPE_5__ {char const* property; int type; } ;
typedef  TYPE_1__ param_dispatch_t ;
typedef  int /*<<< orphan*/  number_type ;
typedef  int /*<<< orphan*/  int_type ;
struct TYPE_6__ {int written; int len; char* data; scalar_t__ on_release; } ;
typedef  TYPE_2__ ebb_buf ;
typedef  int /*<<< orphan*/  bool_type ;
typedef  int /*<<< orphan*/  blob_type ;

/* Variables and functions */
#define  PARAM_TYPE_BLOB 137 
#define  PARAM_TYPE_BODY 136 
#define  PARAM_TYPE_BOOL 135 
#define  PARAM_TYPE_DOUBLE 134 
#define  PARAM_TYPE_FLOAT 133 
#define  PARAM_TYPE_ID 132 
#define  PARAM_TYPE_INT 131 
#define  PARAM_TYPE_POINT 130 
#define  PARAM_TYPE_SIZE 129 
#define  PARAM_TYPE_STRING 128 
 char* ebb_http_header ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,size_t) ; 
 int strlen (char const*) ; 

ebb_buf param_parser_map_http_body(const param_dispatch_t* param_map, size_t len, const char* response_format)
{
	ebb_buf body;
	int i;
	static const char int_type[] = "integer";
	static const char bool_type[] = "boolean";
	static const char number_type[] = "number";
	static const char size_type[] = "size";
	static const char point_type[] = "point";
	static const char string_type[] = "string";
	static const char blob_type[] = "blob";
	size_t body_len = 12;
	for (i = 0; i < len; i++)
	{
		body_len += strlen(param_map[i].property) + 6;
		switch (param_map[i].type)
		{
			case PARAM_TYPE_INT:
			case PARAM_TYPE_ID:
				body_len += sizeof(int_type) - 1;
				break;
			case PARAM_TYPE_FLOAT:
			case PARAM_TYPE_DOUBLE:
				body_len += sizeof(number_type) - 1;
				break;
			case PARAM_TYPE_BOOL:
				body_len += sizeof(bool_type) - 1;
				break;
			case PARAM_TYPE_POINT:
				body_len += sizeof(point_type) - 1;
				break;
			case PARAM_TYPE_SIZE:
				body_len += sizeof(size_type) - 1;
				break;
			case PARAM_TYPE_STRING:
				body_len += sizeof(string_type) - 1;
				break;
			case PARAM_TYPE_BLOB:
			case PARAM_TYPE_BODY:
				body_len += sizeof(blob_type) - 1;
				break;
		}
	}
	if (response_format)
		body_len += 12 + strlen(response_format);
	body_len += 1;
	char* data = (char*)malloc(192 /* the head start for http header */ + body_len);
	snprintf(data, 192, ebb_http_header, body_len);
	body.written = strlen(data);
	memcpy(data + body.written, "{\"request\":{", 12);
	body.written += 12 + 1;
	for (i = 0; i < len; i++)
	{
		data[body.written - 1] = '"';
		size_t property_len = strlen(param_map[i].property);
		memcpy(data + body.written, param_map[i].property, property_len);
		body.written += property_len + 3;
		data[body.written - 3] = '"';
		data[body.written - 2] = ':';
		data[body.written - 1] = '"';
		switch (param_map[i].type)
		{
			case PARAM_TYPE_INT:
			case PARAM_TYPE_ID:
				memcpy(data + body.written, int_type, sizeof(int_type) - 1);
				body.written += sizeof(int_type) + 2;
				break;
			case PARAM_TYPE_FLOAT:
			case PARAM_TYPE_DOUBLE:
				memcpy(data + body.written, number_type, sizeof(number_type) - 1);
				body.written += sizeof(number_type) + 2;
				break;
			case PARAM_TYPE_BOOL:
				memcpy(data + body.written, bool_type, sizeof(bool_type) - 1);
				body.written += sizeof(bool_type) + 2;
				break;
			case PARAM_TYPE_POINT:
				memcpy(data + body.written, point_type, sizeof(point_type) - 1);
				body.written += sizeof(point_type) + 2;
				break;
			case PARAM_TYPE_SIZE:
				memcpy(data + body.written, size_type, sizeof(size_type) - 1);
				body.written += sizeof(size_type) + 2;
				break;
			case PARAM_TYPE_STRING:
				memcpy(data + body.written, string_type, sizeof(string_type) - 1);
				body.written += sizeof(string_type) + 2;
				break;
			case PARAM_TYPE_BLOB:
			case PARAM_TYPE_BODY:
				memcpy(data + body.written, blob_type, sizeof(blob_type) - 1);
				body.written += sizeof(blob_type) + 2;
				break;
		}
		data[body.written - 3] = '"';
		data[body.written - 2] = (i == len - 1) ? '}' : ',';
	}
	if (response_format)
	{
		memcpy(data + body.written - 1, ",\"response\":", 12);
		body.written += 11;
		size_t response_len = strlen(response_format);
		memcpy(data + body.written, response_format, response_len);
		body.written += response_len + 1;
	}
	data[body.written - 1] = '}';
	data[body.written] = '\n';
	body.len = body.written + 1;
	body.data = data;
	body.on_release = 0;
	return body;
}