#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  avctx; TYPE_3__ gb; } ;
typedef  TYPE_1__ EXRContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int bytestream2_get_bytes_left (TYPE_3__*) ; 
 int bytestream2_get_le32 (TYPE_3__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int check_header_variable(EXRContext *s,
                                 const char *value_name,
                                 const char *value_type,
                                 unsigned int minimum_length)
{
    int var_size = -1;

    if (bytestream2_get_bytes_left(&s->gb) >= minimum_length &&
        !strcmp(s->gb.buffer, value_name)) {
        // found value_name, jump to value_type (null terminated strings)
        s->gb.buffer += strlen(value_name) + 1;
        if (!strcmp(s->gb.buffer, value_type)) {
            s->gb.buffer += strlen(value_type) + 1;
            var_size = bytestream2_get_le32(&s->gb);
            // don't go read past boundaries
            if (var_size > bytestream2_get_bytes_left(&s->gb))
                var_size = 0;
        } else {
            // value_type not found, reset the buffer
            s->gb.buffer -= strlen(value_name) + 1;
            av_log(s->avctx, AV_LOG_WARNING,
                   "Unknown data type %s for header variable %s.\n",
                   value_type, value_name);
        }
    }

    return var_size;
}