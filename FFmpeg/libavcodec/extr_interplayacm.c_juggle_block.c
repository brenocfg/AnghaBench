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
struct TYPE_3__ {int level; unsigned int rows; int* block; int* wrapbuf; int cols; } ;
typedef  TYPE_1__ InterplayACMContext ;

/* Variables and functions */
 int /*<<< orphan*/  juggle (int*,int*,unsigned int,unsigned int) ; 

__attribute__((used)) static void juggle_block(InterplayACMContext *s)
{
    unsigned sub_count, sub_len, todo_count, step_subcount, i;
    int *wrap_p, *block_p, *p;

    /* juggle only if subblock_len > 1 */
    if (s->level == 0)
        return;

    /* 2048 / subblock_len */
    if (s->level > 9)
        step_subcount = 1;
    else
        step_subcount = (2048 >> s->level) - 2;

    /* Apply juggle()  (rows)x(cols)
     * from (step_subcount * 2)            x (subblock_len/2)
     * to   (step_subcount * subblock_len) x (1)
     */
    todo_count = s->rows;
    block_p = s->block;
    while (1) {
        wrap_p = s->wrapbuf;
        sub_count = step_subcount;
        if (sub_count > todo_count)
            sub_count = todo_count;

        sub_len = s->cols / 2;
        sub_count *= 2;

        juggle(wrap_p, block_p, sub_len, sub_count);
        wrap_p += sub_len * 2;

        for (i = 0, p = block_p; i < sub_count; i++) {
            p[0]++;
            p += sub_len;
        }

        while (sub_len > 1) {
            sub_len /= 2;
            sub_count *= 2;
            juggle(wrap_p, block_p, sub_len, sub_count);
            wrap_p += sub_len * 2;
        }

        if (todo_count <= step_subcount)
            break;

        todo_count -= step_subcount;
        block_p += step_subcount << s->level;
    }
}