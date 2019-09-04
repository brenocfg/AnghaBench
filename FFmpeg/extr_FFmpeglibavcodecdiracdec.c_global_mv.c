#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_8__ {int** mv; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
struct TYPE_9__ {TYPE_1__* globalmc; } ;
struct TYPE_7__ {int zrs_exp; int perspective_exp; int** zrs; int* pan_tilt; int* perspective; } ;
typedef  TYPE_3__ DiracContext ;
typedef  TYPE_4__ DiracBlock ;

/* Variables and functions */

__attribute__((used)) static void global_mv(DiracContext *s, DiracBlock *block, int x, int y, int ref)
{
    int ez      = s->globalmc[ref].zrs_exp;
    int ep      = s->globalmc[ref].perspective_exp;
    int (*A)[2] = s->globalmc[ref].zrs;
    int *b      = s->globalmc[ref].pan_tilt;
    int *c      = s->globalmc[ref].perspective;

    int64_t m   = (1<<ep) - (c[0]*(int64_t)x + c[1]*(int64_t)y);
    int64_t mx  = m * (int64_t)((A[0][0] * (int64_t)x + A[0][1]*(int64_t)y) + (1<<ez) * b[0]);
    int64_t my  = m * (int64_t)((A[1][0] * (int64_t)x + A[1][1]*(int64_t)y) + (1<<ez) * b[1]);

    block->u.mv[ref][0] = (mx + (1<<(ez+ep))) >> (ez+ep);
    block->u.mv[ref][1] = (my + (1<<(ez+ep))) >> (ez+ep);
}