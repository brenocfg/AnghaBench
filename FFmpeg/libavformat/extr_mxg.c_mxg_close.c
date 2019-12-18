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
struct AVFormatContext {TYPE_1__* priv_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ MXGContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxg_close(struct AVFormatContext *s)
{
    MXGContext *mxg = s->priv_data;
    av_freep(&mxg->buffer);
    return 0;
}