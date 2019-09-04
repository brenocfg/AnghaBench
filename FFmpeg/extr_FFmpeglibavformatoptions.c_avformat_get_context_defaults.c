#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  io_close; int /*<<< orphan*/  io_open; int /*<<< orphan*/ * av_class; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_format_context_class ; 
 int /*<<< orphan*/  av_opt_set_defaults (TYPE_1__*) ; 
 int /*<<< orphan*/  io_close_default ; 
 int /*<<< orphan*/  io_open_default ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void avformat_get_context_defaults(AVFormatContext *s)
{
    memset(s, 0, sizeof(AVFormatContext));

    s->av_class = &av_format_context_class;

    s->io_open  = io_open_default;
    s->io_close = io_close_default;

    av_opt_set_defaults(s);
}