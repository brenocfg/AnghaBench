#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_2__ {int text_pos; int byte_count; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ MovTextContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprint_append_data (int /*<<< orphan*/ *,char const*,int) ; 
 int utf8_strlen (char const*,int) ; 

__attribute__((used)) static void mov_text_text_cb(void *priv, const char *text, int len)
{
    uint16_t utf8_len = utf8_strlen(text, len);
    MovTextContext *s = priv;
    av_bprint_append_data(&s->buffer, text, len);
    // If it's not utf-8, just use the byte length
    s->text_pos += utf8_len ? utf8_len : len;
    s->byte_count += len;
}