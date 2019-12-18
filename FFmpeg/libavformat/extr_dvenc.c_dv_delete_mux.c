#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int n_ast; int /*<<< orphan*/ * audio_data; } ;
typedef  TYPE_1__ DVMuxContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_fifo_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dv_delete_mux(DVMuxContext *c)
{
    int i;
    for (i=0; i < c->n_ast; i++)
        av_fifo_freep(&c->audio_data[i]);
}