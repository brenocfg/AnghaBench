#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
struct TYPE_6__ {int /*<<< orphan*/  wrap_buf; int /*<<< orphan*/  fifo_buf; TYPE_2__* headers; } ;
typedef  TYPE_1__ FLACParseContext ;
typedef  TYPE_2__ FLACHeaderMarker ;
typedef  TYPE_3__ AVCodecParserContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_fifo_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (TYPE_2__*) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flac_parse_close(AVCodecParserContext *c)
{
    FLACParseContext *fpc = c->priv_data;
    FLACHeaderMarker *curr = fpc->headers, *temp;

    while (curr) {
        temp = curr->next;
        av_free(curr);
        curr = temp;
    }
    fpc->headers = NULL;
    av_fifo_freep(&fpc->fifo_buf);
    av_freep(&fpc->wrap_buf);
}