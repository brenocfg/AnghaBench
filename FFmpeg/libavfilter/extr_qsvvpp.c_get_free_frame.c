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
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  surface; } ;
typedef  TYPE_1__ QSVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* av_mallocz (int) ; 

__attribute__((used)) static QSVFrame *get_free_frame(QSVFrame **list)
{
    QSVFrame *out = *list;

    for (; out; out = out->next) {
        if (!out->surface)
            break;
    }

    if (!out) {
        out = av_mallocz(sizeof(*out));
        if (!out) {
            av_log(NULL, AV_LOG_ERROR, "Can't alloc new output frame.\n");
            return NULL;
        }
        out->next  = *list;
        *list      = out;
    }

    return out;
}