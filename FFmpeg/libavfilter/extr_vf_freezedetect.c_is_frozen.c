#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  double uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {int* width; double* height; unsigned long long bitdepth; double noise; int /*<<< orphan*/  (* sad ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,double,double*) ;} ;
typedef  TYPE_1__ FreezeDetectContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,double,double*) ; 

__attribute__((used)) static int is_frozen(FreezeDetectContext *s, AVFrame *reference, AVFrame *frame)
{
    uint64_t sad = 0;
    uint64_t count = 0;
    double mafd;
    for (int plane = 0; plane < 4; plane++) {
        if (s->width[plane]) {
            uint64_t plane_sad;
            s->sad(frame->data[plane], frame->linesize[plane],
                   reference->data[plane], reference->linesize[plane],
                   s->width[plane], s->height[plane], &plane_sad);
            sad += plane_sad;
            count += s->width[plane] * s->height[plane];
        }
    }
    emms_c();
    mafd = (double)sad / count / (1ULL << s->bitdepth);
    return (mafd <= s->noise);
}