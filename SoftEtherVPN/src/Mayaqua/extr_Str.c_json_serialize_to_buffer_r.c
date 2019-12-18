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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  int /*<<< orphan*/  JSON_OBJECT ;
typedef  int /*<<< orphan*/  JSON_ARRAY ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND_INDENT (int) ; 
 int /*<<< orphan*/  APPEND_STRING (char*) ; 
 int /*<<< orphan*/  Copy (char*,char*,int) ; 
#define  JSON_TYPE_ARRAY 134 
#define  JSON_TYPE_BOOL 133 
#define  JSON_TYPE_ERROR 132 
#define  JSON_TYPE_NULL 131 
#define  JSON_TYPE_NUMBER 130 
#define  JSON_TYPE_OBJECT 129 
#define  JSON_TYPE_STRING 128 
 int /*<<< orphan*/ * JsonArrayGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsonArrayGetCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonGet (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  JsonGetCount (int /*<<< orphan*/ *) ; 
 char* JsonGetName (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * JsonValueGetArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonValueGetBool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonValueGetNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonValueGetObject (int /*<<< orphan*/ *) ; 
 char* JsonValueGetStr (int /*<<< orphan*/ *) ; 
 int JsonValueGetType (int /*<<< orphan*/ *) ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  ToStr64 (char*,int /*<<< orphan*/ ) ; 
 int json_serialize_string (char*,char*) ; 

__attribute__((used)) static int json_serialize_to_buffer_r(JSON_VALUE *value, char *buf, int level, int is_pretty, char *num_buf)
{
	char *key = NULL, *string = NULL;
	JSON_VALUE *temp_value = NULL;
	JSON_ARRAY *array = NULL;
	JSON_OBJECT *object = NULL;
	UINT i = 0, count = 0;
	UINT64 num = 0;
	int written = -1, written_total = 0;
	char tmp[32];

	switch (JsonValueGetType(value)) {
	case JSON_TYPE_ARRAY:
		array = JsonValueGetArray(value);
		count = JsonArrayGetCount(array);
		APPEND_STRING("[");
		if (count > 0 && is_pretty) {
			APPEND_STRING("\n");
		}
		for (i = 0; i < count; i++) {
			if (is_pretty) {
				APPEND_INDENT(level + 1);
			}
			temp_value = JsonArrayGet(array, i);
			written = json_serialize_to_buffer_r(temp_value, buf, level + 1, is_pretty, num_buf);
			if (written < 0) {
				return -1;
			}
			if (buf != NULL) {
				buf += written;
			}
			written_total += written;
			if (i < (count - 1)) {
				APPEND_STRING(",");
			}
			if (is_pretty) {
				APPEND_STRING("\n");
			}
		}
		if (count > 0 && is_pretty) {
			APPEND_INDENT(level);
		}
		APPEND_STRING("]");
		return written_total;
	case JSON_TYPE_OBJECT:
		object = JsonValueGetObject(value);
		count = JsonGetCount(object);
		APPEND_STRING("{");
		if (count > 0 && is_pretty) {
			APPEND_STRING("\n");
		}
		for (i = 0; i < count; i++) {
			key = JsonGetName(object, i);
			if (key == NULL) {
				return -1;
			}
			if (is_pretty) {
				APPEND_INDENT(level + 1);
			}
			written = json_serialize_string(key, buf);
			if (written < 0) {
				return -1;
			}
			if (buf != NULL) {
				buf += written;
			}
			written_total += written;
			APPEND_STRING(":");
			if (is_pretty) {
				APPEND_STRING(" ");
			}
			temp_value = JsonGet(object, key);
			written = json_serialize_to_buffer_r(temp_value, buf, level + 1, is_pretty, num_buf);
			if (written < 0) {
				return -1;
			}
			if (buf != NULL) {
				buf += written;
			}
			written_total += written;
			if (i < (count - 1)) {
				APPEND_STRING(",");
			}
			if (is_pretty) {
				APPEND_STRING("\n");
			}
		}
		if (count > 0 && is_pretty) {
			APPEND_INDENT(level);
		}
		APPEND_STRING("}");
		return written_total;
	case JSON_TYPE_STRING:
		string = JsonValueGetStr(value);
		if (string == NULL) {
			return -1;
		}
		written = json_serialize_string(string, buf);
		if (written < 0) {
			return -1;
		}
		if (buf != NULL) {
			buf += written;
		}
		written_total += written;
		return written_total;
	case JSON_TYPE_BOOL:
		if (JsonValueGetBool(value)) {
			APPEND_STRING("true");
		}
		else {
			APPEND_STRING("false");
		}
		return written_total;
	case JSON_TYPE_NUMBER:
		num = JsonValueGetNumber(value);
		if (buf != NULL) {
			num_buf = buf;
		}
		ToStr64(tmp, num);
		Copy(num_buf, tmp, StrLen(tmp));
		written = StrLen(tmp);
		if (buf != NULL) {
			buf += written;
		}
		written_total += written;
		return written_total;
	case JSON_TYPE_NULL:
		APPEND_STRING("null");
		return written_total;
	case JSON_TYPE_ERROR:
		return -1;
	default:
		return -1;
	}
}