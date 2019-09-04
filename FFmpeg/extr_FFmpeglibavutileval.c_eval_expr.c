#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_7__ {size_t const_index; double (* func0 ) (double) ;double (* func1 ) (int /*<<< orphan*/ ,double) ;double (* func2 ) (int /*<<< orphan*/ ,double,double) ;} ;
struct TYPE_9__ {int type; double value; struct TYPE_9__** param; TYPE_1__ a; } ;
struct TYPE_8__ {double* const_values; double* var; int /*<<< orphan*/  opaque; } ;
typedef  TYPE_2__ Parser ;
typedef  TYPE_3__ AVExpr ;

/* Variables and functions */
 size_t AV_LOG_INFO ; 
 int /*<<< orphan*/  CONFIG_FTRAPV ; 
 double DBL_MAX ; 
 double INFINITY ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  INT_MIN ; 
 int M_PI ; 
 double NAN ; 
 double UINT64_MAX ; 
 int /*<<< orphan*/  VARS ; 
 double atan2 (double,double) ; 
 size_t av_clip (double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double av_clipd (double,double,double) ; 
 double av_gcd (double,double) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int,char*,double) ; 
 double ceil (double) ; 
#define  e_add 172 
#define  e_atan2 171 
#define  e_between 170 
#define  e_bitand 169 
#define  e_bitor 168 
#define  e_ceil 167 
#define  e_clip 166 
#define  e_const 165 
#define  e_div 164 
#define  e_eq 163 
#define  e_floor 162 
#define  e_func0 161 
#define  e_func1 160 
#define  e_func2 159 
#define  e_gauss 158 
#define  e_gcd 157 
#define  e_gt 156 
#define  e_gte 155 
#define  e_hypot 154 
#define  e_if 153 
#define  e_ifnot 152 
#define  e_isinf 151 
#define  e_isnan 150 
#define  e_last 149 
#define  e_ld 148 
#define  e_lerp 147 
#define  e_lt 146 
#define  e_lte 145 
#define  e_max 144 
#define  e_min 143 
#define  e_mod 142 
#define  e_mul 141 
#define  e_not 140 
#define  e_pow 139 
#define  e_print 138 
#define  e_random 137 
#define  e_root 136 
#define  e_round 135 
#define  e_sqrt 134 
#define  e_squish 133 
#define  e_st 132 
#define  e_taylor 131 
#define  e_trunc 130 
#define  e_value 129 
#define  e_while 128 
 double exp (double) ; 
 double* ff_reverse ; 
 double floor (double) ; 
 double hypot (double,double) ; 
 int /*<<< orphan*/  isinf (double) ; 
 int /*<<< orphan*/  isnan (double) ; 
 double pow (double,double) ; 
 double round (double) ; 
 double sqrt (int) ; 
 double stub1 (double) ; 
 double stub2 (int /*<<< orphan*/ ,double) ; 
 double stub3 (int /*<<< orphan*/ ,double,double) ; 
 double trunc (double) ; 

__attribute__((used)) static double eval_expr(Parser *p, AVExpr *e)
{
    switch (e->type) {
        case e_value:  return e->value;
        case e_const:  return e->value * p->const_values[e->a.const_index];
        case e_func0:  return e->value * e->a.func0(eval_expr(p, e->param[0]));
        case e_func1:  return e->value * e->a.func1(p->opaque, eval_expr(p, e->param[0]));
        case e_func2:  return e->value * e->a.func2(p->opaque, eval_expr(p, e->param[0]), eval_expr(p, e->param[1]));
        case e_squish: return 1/(1+exp(4*eval_expr(p, e->param[0])));
        case e_gauss: { double d = eval_expr(p, e->param[0]); return exp(-d*d/2)/sqrt(2*M_PI); }
        case e_ld:     return e->value * p->var[av_clip(eval_expr(p, e->param[0]), 0, VARS-1)];
        case e_isnan:  return e->value * !!isnan(eval_expr(p, e->param[0]));
        case e_isinf:  return e->value * !!isinf(eval_expr(p, e->param[0]));
        case e_floor:  return e->value * floor(eval_expr(p, e->param[0]));
        case e_ceil :  return e->value * ceil (eval_expr(p, e->param[0]));
        case e_trunc:  return e->value * trunc(eval_expr(p, e->param[0]));
        case e_round:  return e->value * round(eval_expr(p, e->param[0]));
        case e_sqrt:   return e->value * sqrt (eval_expr(p, e->param[0]));
        case e_not:    return e->value * (eval_expr(p, e->param[0]) == 0);
        case e_if:     return e->value * (eval_expr(p, e->param[0]) ? eval_expr(p, e->param[1]) :
                                          e->param[2] ? eval_expr(p, e->param[2]) : 0);
        case e_ifnot:  return e->value * (!eval_expr(p, e->param[0]) ? eval_expr(p, e->param[1]) :
                                          e->param[2] ? eval_expr(p, e->param[2]) : 0);
        case e_clip: {
            double x = eval_expr(p, e->param[0]);
            double min = eval_expr(p, e->param[1]), max = eval_expr(p, e->param[2]);
            if (isnan(min) || isnan(max) || isnan(x) || min > max)
                return NAN;
            return e->value * av_clipd(eval_expr(p, e->param[0]), min, max);
        }
        case e_between: {
            double d = eval_expr(p, e->param[0]);
            return e->value * (d >= eval_expr(p, e->param[1]) &&
                               d <= eval_expr(p, e->param[2]));
        }
        case e_lerp: {
            double v0 = eval_expr(p, e->param[0]);
            double v1 = eval_expr(p, e->param[1]);
            double f  = eval_expr(p, e->param[2]);
            return v0 + (v1 - v0) * f;
        }
        case e_print: {
            double x = eval_expr(p, e->param[0]);
            int level = e->param[1] ? av_clip(eval_expr(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            return x;
        }
        case e_random:{
            int idx= av_clip(eval_expr(p, e->param[0]), 0, VARS-1);
            uint64_t r= isnan(p->var[idx]) ? 0 : p->var[idx];
            r= r*1664525+1013904223;
            p->var[idx]= r;
            return e->value * (r * (1.0/UINT64_MAX));
        }
        case e_while: {
            double d = NAN;
            while (eval_expr(p, e->param[0]))
                d=eval_expr(p, e->param[1]);
            return d;
        }
        case e_taylor: {
            double t = 1, d = 0, v;
            double x = eval_expr(p, e->param[1]);
            int id = e->param[2] ? av_clip(eval_expr(p, e->param[2]), 0, VARS-1) : 0;
            int i;
            double var0 = p->var[id];
            for(i=0; i<1000; i++) {
                double ld = d;
                p->var[id] = i;
                v = eval_expr(p, e->param[0]);
                d += t*v;
                if(ld==d && v)
                    break;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            return d;
        }
        case e_root: {
            int i, j;
            double low = -1, high = -1, v, low_v = -DBL_MAX, high_v = DBL_MAX;
            double var0 = p->var[0];
            double x_max = eval_expr(p, e->param[1]);
            for(i=-1; i<1024; i++) {
                if(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } else {
                    p->var[0] = x_max*pow(0.9, i-255);
                    if (i&1) p->var[0] *= -1;
                    if (i&2) p->var[0] += low;
                    else     p->var[0] += high;
                }
                v = eval_expr(p, e->param[0]);
                if (v<=0 && v>low_v) {
                    low    = p->var[0];
                    low_v  = v;
                }
                if (v>=0 && v<high_v) {
                    high   = p->var[0];
                    high_v = v;
                }
                if (low>=0 && high>=0){
                    for (j=0; j<1000; j++) {
                        p->var[0] = (low+high)*0.5;
                        if (low == p->var[0] || high == p->var[0])
                            break;
                        v = eval_expr(p, e->param[0]);
                        if (v<=0) low = p->var[0];
                        if (v>=0) high= p->var[0];
                        if (isnan(v)) {
                            low = high = v;
                            break;
                        }
                    }
                    break;
                }
            }
            p->var[0] = var0;
            return -low_v<high_v ? low : high;
        }
        default: {
            double d = eval_expr(p, e->param[0]);
            double d2 = eval_expr(p, e->param[1]);
            switch (e->type) {
                case e_mod: return e->value * (d - floor((!CONFIG_FTRAPV || d2) ? d / d2 : d * INFINITY) * d2);
                case e_gcd: return e->value * av_gcd(d,d2);
                case e_max: return e->value * (d >  d2 ?   d : d2);
                case e_min: return e->value * (d <  d2 ?   d : d2);
                case e_eq:  return e->value * (d == d2 ? 1.0 : 0.0);
                case e_gt:  return e->value * (d >  d2 ? 1.0 : 0.0);
                case e_gte: return e->value * (d >= d2 ? 1.0 : 0.0);
                case e_lt:  return e->value * (d <  d2 ? 1.0 : 0.0);
                case e_lte: return e->value * (d <= d2 ? 1.0 : 0.0);
                case e_pow: return e->value * pow(d, d2);
                case e_mul: return e->value * (d * d2);
                case e_div: return e->value * ((!CONFIG_FTRAPV || d2 ) ? (d / d2) : d * INFINITY);
                case e_add: return e->value * (d + d2);
                case e_last:return e->value * d2;
                case e_st : return e->value * (p->var[av_clip(d, 0, VARS-1)]= d2);
                case e_hypot:return e->value * hypot(d, d2);
                case e_atan2:return e->value * atan2(d, d2);
                case e_bitand: return isnan(d) || isnan(d2) ? NAN : e->value * ((long int)d & (long int)d2);
                case e_bitor:  return isnan(d) || isnan(d2) ? NAN : e->value * ((long int)d | (long int)d2);
            }
        }
    }
    return NAN;
}