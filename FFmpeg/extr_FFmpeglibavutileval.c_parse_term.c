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
struct TYPE_4__ {char* s; } ;
typedef  TYPE_1__ Parser ;
typedef  int /*<<< orphan*/  AVExpr ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_expr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_div ; 
 int /*<<< orphan*/  e_mul ; 
 int /*<<< orphan*/ * make_eval_expr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int parse_factor (int /*<<< orphan*/ **,TYPE_1__*) ; 

__attribute__((used)) static int parse_term(AVExpr **e, Parser *p)
{
    int ret;
    AVExpr *e0, *e1, *e2;
    if ((ret = parse_factor(&e0, p)) < 0)
        return ret;
    while (p->s[0]=='*' || p->s[0]=='/') {
        int c= *p->s++;
        e1 = e0;
        if ((ret = parse_factor(&e2, p)) < 0) {
            av_expr_free(e1);
            return ret;
        }
        e0 = make_eval_expr(c == '*' ? e_mul : e_div, 1, e1, e2);
        if (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            return AVERROR(ENOMEM);
        }
    }
    *e = e0;
    return 0;
}