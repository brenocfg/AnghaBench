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
struct TYPE_3__ {int type; struct TYPE_3__** param; } ;
typedef  TYPE_1__ AVExpr ;

/* Variables and functions */
#define  e_between 151 
#define  e_ceil 150 
#define  e_clip 149 
#define  e_const 148 
#define  e_floor 147 
#define  e_func0 146 
#define  e_func1 145 
#define  e_gauss 144 
#define  e_if 143 
#define  e_ifnot 142 
#define  e_isinf 141 
#define  e_isnan 140 
#define  e_ld 139 
#define  e_lerp 138 
#define  e_not 137 
#define  e_print 136 
#define  e_random 135 
#define  e_round 134 
#define  e_sgn 133 
#define  e_sqrt 132 
#define  e_squish 131 
#define  e_taylor 130 
#define  e_trunc 129 
#define  e_value 128 

__attribute__((used)) static int verify_expr(AVExpr *e)
{
    if (!e) return 0;
    switch (e->type) {
        case e_value:
        case e_const: return 1;
        case e_func0:
        case e_func1:
        case e_squish:
        case e_ld:
        case e_gauss:
        case e_isnan:
        case e_isinf:
        case e_floor:
        case e_ceil:
        case e_trunc:
        case e_round:
        case e_sqrt:
        case e_not:
        case e_random:
        case e_sgn:
            return verify_expr(e->param[0]) && !e->param[1];
        case e_print:
            return verify_expr(e->param[0])
                   && (!e->param[1] || verify_expr(e->param[1]));
        case e_if:
        case e_ifnot:
        case e_taylor:
            return verify_expr(e->param[0]) && verify_expr(e->param[1])
                   && (!e->param[2] || verify_expr(e->param[2]));
        case e_between:
        case e_clip:
        case e_lerp:
            return verify_expr(e->param[0]) &&
                   verify_expr(e->param[1]) &&
                   verify_expr(e->param[2]);
        default: return verify_expr(e->param[0]) && verify_expr(e->param[1]) && !e->param[2];
    }
}