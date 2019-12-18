#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  line; } ;
struct TYPE_4__ {char* str_val; int /*<<< orphan*/  kind; int /*<<< orphan*/  mod; TYPE_1__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_MULTILINE ; 
 int /*<<< orphan*/  TOKEN_STR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buf_push (char*,char) ; 
 int /*<<< orphan*/  error_here (char*,...) ; 
 char* escape_to_char ; 
 char scan_hex_escape () ; 
 char* stream ; 
 TYPE_2__ token ; 

void scan_str(void) {
    assert(*stream == '"');
    stream++;
    char *str = NULL;
    if (stream[0] == '"' && stream[1] == '"') {
        stream += 2;
        while (*stream) {
            if (stream[0] == '"' && stream[1] == '"' && stream[2] == '"') {
                stream += 3;
                break;
            }
            if (*stream != '\r') {
                // TODO: Should probably just read files in text mode instead.
                buf_push(str, *stream);
            }
            if (*stream == '\n') {
                token.pos.line++;
            }
            stream++;
        }
        if (!*stream) {
            error_here("Unexpected end of file within multi-line string literal");
        }
        token.mod = MOD_MULTILINE;
    } else {
        while (*stream && *stream != '"') {
            char val = *stream;
            if (val == '\n') {
                error_here("String literal cannot contain newline");
                break;
            } else if (val == '\\') {
                stream++;
                if (*stream == 'x') {
                    val = scan_hex_escape();
                } else {
                    val = escape_to_char[(unsigned char)*stream];
                    if (val == 0 && *stream != '0') {
                        error_here("Invalid string literal escape '\\%c'", *stream);
                    }
                    stream++;
                }
            } else {
                stream++;
            }
            buf_push(str, val);
        }
        if (*stream) {
            stream++;
        } else {
            error_here("Unexpected end of file within string literal");
        }
    }
    buf_push(str, 0);
    token.kind = TOKEN_STR;
    token.str_val = str;
}