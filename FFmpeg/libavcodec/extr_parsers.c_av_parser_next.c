#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ AVCodecParser ;

/* Variables and functions */
 int /*<<< orphan*/  av_parser_init_next ; 
 int /*<<< orphan*/  av_parser_next_init ; 
 int /*<<< orphan*/  ff_thread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__* parser_list ; 

AVCodecParser *av_parser_next(const AVCodecParser *p)
{
    ff_thread_once(&av_parser_next_init, av_parser_init_next);

    if (p)
        return p->next;
    else
        return (AVCodecParser*)parser_list[0];
}