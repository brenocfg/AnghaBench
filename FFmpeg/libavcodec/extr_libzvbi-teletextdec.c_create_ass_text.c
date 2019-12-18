#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  readorder; } ;
typedef  TYPE_1__ TeletextContext ;
struct TYPE_9__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_2__ AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprint_is_complete (TYPE_2__*) ; 
 int /*<<< orphan*/  ff_ass_bprint_text_event (TYPE_2__*,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* ff_ass_get_dialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static char *create_ass_text(TeletextContext *ctx, const char *text)
{
    char *dialog;
    AVBPrint buf;

    av_bprint_init(&buf, 0, AV_BPRINT_SIZE_UNLIMITED);
    ff_ass_bprint_text_event(&buf, text, strlen(text), "", 0);
    if (!av_bprint_is_complete(&buf)) {
        av_bprint_finalize(&buf, NULL);
        return NULL;
    }
    dialog = ff_ass_get_dialog(ctx->readorder++, 0, NULL, NULL, buf.str);
    av_bprint_finalize(&buf, NULL);
    return dialog;
}