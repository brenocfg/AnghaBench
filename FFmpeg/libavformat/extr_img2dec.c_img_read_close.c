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
struct TYPE_2__ {int /*<<< orphan*/  globstate; scalar_t__ use_glob; } ;
typedef  TYPE_1__ VideoDemuxData ;

/* Variables and functions */
 int /*<<< orphan*/  globfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int img_read_close(struct AVFormatContext* s1)
{
#if HAVE_GLOB
    VideoDemuxData *s = s1->priv_data;
    if (s->use_glob) {
        globfree(&s->globstate);
    }
#endif
    return 0;
}