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
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND_STRING (char*) ; 
 size_t StrLen (char*) ; 

__attribute__((used)) static int json_serialize_string(char *string, char *buf) {
	UINT i = 0, len = StrLen(string);
	char c = '\0';
	int written = -1, written_total = 0;
	APPEND_STRING("\"");
	for (i = 0; i < len; i++) {
		c = string[i];
		switch (c) {
		case '\"': APPEND_STRING("\\\""); break;
		case '\\': APPEND_STRING("\\\\"); break;
		case '/':  APPEND_STRING("\\/"); break; /* to make json embeddable in xml\/html */
		case '\b': APPEND_STRING("\\b"); break;
		case '\f': APPEND_STRING("\\f"); break;
		case '\n': APPEND_STRING("\\n"); break;
		case '\r': APPEND_STRING("\\r"); break;
		case '\t': APPEND_STRING("\\t"); break;
		case '\x00': APPEND_STRING("\\u0000"); break;
		case '\x01': APPEND_STRING("\\u0001"); break;
		case '\x02': APPEND_STRING("\\u0002"); break;
		case '\x03': APPEND_STRING("\\u0003"); break;
		case '\x04': APPEND_STRING("\\u0004"); break;
		case '\x05': APPEND_STRING("\\u0005"); break;
		case '\x06': APPEND_STRING("\\u0006"); break;
		case '\x07': APPEND_STRING("\\u0007"); break;
			/* '\x08' duplicate: '\b' */
			/* '\x09' duplicate: '\t' */
			/* '\x0a' duplicate: '\n' */
		case '\x0b': APPEND_STRING("\\u000b"); break;
			/* '\x0c' duplicate: '\f' */
			/* '\x0d' duplicate: '\r' */
		case '\x0e': APPEND_STRING("\\u000e"); break;
		case '\x0f': APPEND_STRING("\\u000f"); break;
		case '\x10': APPEND_STRING("\\u0010"); break;
		case '\x11': APPEND_STRING("\\u0011"); break;
		case '\x12': APPEND_STRING("\\u0012"); break;
		case '\x13': APPEND_STRING("\\u0013"); break;
		case '\x14': APPEND_STRING("\\u0014"); break;
		case '\x15': APPEND_STRING("\\u0015"); break;
		case '\x16': APPEND_STRING("\\u0016"); break;
		case '\x17': APPEND_STRING("\\u0017"); break;
		case '\x18': APPEND_STRING("\\u0018"); break;
		case '\x19': APPEND_STRING("\\u0019"); break;
		case '\x1a': APPEND_STRING("\\u001a"); break;
		case '\x1b': APPEND_STRING("\\u001b"); break;
		case '\x1c': APPEND_STRING("\\u001c"); break;
		case '\x1d': APPEND_STRING("\\u001d"); break;
		case '\x1e': APPEND_STRING("\\u001e"); break;
		case '\x1f': APPEND_STRING("\\u001f"); break;
		default:
			if (buf != NULL) {
				buf[0] = c;
				buf += 1;
			}
			written_total += 1;
			break;
		}
	}
	APPEND_STRING("\"");
	return written_total;
}