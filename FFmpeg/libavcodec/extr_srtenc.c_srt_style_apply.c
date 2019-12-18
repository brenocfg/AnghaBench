#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int primary_color; int font_name; scalar_t__ font_size; scalar_t__ bold; scalar_t__ italic; scalar_t__ underline; int alignment; } ;
struct TYPE_7__ {int alignment_applied; int /*<<< orphan*/  ass_ctx; } ;
typedef  TYPE_1__ SRTContext ;
typedef  TYPE_2__ ASSStyle ;

/* Variables and functions */
 int ASS_DEFAULT_ALIGNMENT ; 
 scalar_t__ ASS_DEFAULT_BOLD ; 
 int ASS_DEFAULT_COLOR ; 
 int /*<<< orphan*/  ASS_DEFAULT_FONT ; 
 scalar_t__ ASS_DEFAULT_FONT_SIZE ; 
 scalar_t__ ASS_DEFAULT_ITALIC ; 
 scalar_t__ ASS_DEFAULT_UNDERLINE ; 
 TYPE_2__* ff_ass_style_get (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  srt_print (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  srt_stack_push (TYPE_1__*,unsigned char) ; 
 scalar_t__ strcmp (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void srt_style_apply(SRTContext *s, const char *style)
{
    ASSStyle *st = ff_ass_style_get(s->ass_ctx, style);
    if (st) {
        int c = st->primary_color & 0xFFFFFF;
        if (st->font_name && strcmp(st->font_name, ASS_DEFAULT_FONT) ||
            st->font_size != ASS_DEFAULT_FONT_SIZE ||
            c != ASS_DEFAULT_COLOR) {
            srt_print(s, "<font");
            if (st->font_name && strcmp(st->font_name, ASS_DEFAULT_FONT))
                srt_print(s, " face=\"%s\"", st->font_name);
            if (st->font_size != ASS_DEFAULT_FONT_SIZE)
                srt_print(s, " size=\"%d\"", st->font_size);
            if (c != ASS_DEFAULT_COLOR)
                srt_print(s, " color=\"#%06x\"",
                          (c & 0xFF0000) >> 16 | c & 0xFF00 | (c & 0xFF) << 16);
            srt_print(s, ">");
            srt_stack_push(s, 'f');
        }
        if (st->bold != ASS_DEFAULT_BOLD) {
            srt_print(s, "<b>");
            srt_stack_push(s, 'b');
        }
        if (st->italic != ASS_DEFAULT_ITALIC) {
            srt_print(s, "<i>");
            srt_stack_push(s, 'i');
        }
        if (st->underline != ASS_DEFAULT_UNDERLINE) {
            srt_print(s, "<u>");
            srt_stack_push(s, 'u');
        }
        if (st->alignment != ASS_DEFAULT_ALIGNMENT) {
            srt_print(s, "{\\an%d}", st->alignment);
            s->alignment_applied = 1;
        }
    }
}