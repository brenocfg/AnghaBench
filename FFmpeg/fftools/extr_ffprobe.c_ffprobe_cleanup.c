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
struct TYPE_3__ {int /*<<< orphan*/  entries_to_show; } ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_mutex ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* sections ; 

__attribute__((used)) static void ffprobe_cleanup(int ret)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(sections); i++)
        av_dict_free(&(sections[i].entries_to_show));

#if HAVE_THREADS
    pthread_mutex_destroy(&log_mutex);
#endif
}