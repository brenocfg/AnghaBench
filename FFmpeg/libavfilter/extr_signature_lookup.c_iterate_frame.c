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
struct TYPE_4__ {struct TYPE_4__* prev; struct TYPE_4__* next; } ;
typedef  TYPE_1__ FineSignature ;

/* Variables and functions */
 int DIR_NEXT ; 
 int DIR_NEXT_END ; 
 int DIR_PREV ; 
 int DIR_PREV_END ; 

__attribute__((used)) static int iterate_frame(double frr, FineSignature **a, FineSignature **b, int fcount, int *bcount, int dir)
{
    int step;

    /* between 1 and 2, because frr is between 1 and 2 */
    step = ((int) 0.5 + fcount     * frr) /* current frame */
          -((int) 0.5 + (fcount-1) * frr);/* last frame */

    if (dir == DIR_NEXT) {
        if (frr >= 1.0) {
            if ((*a)->next) {
                *a = (*a)->next;
            } else {
                return DIR_NEXT_END;
            }

            if (step == 1) {
                if ((*b)->next) {
                    *b = (*b)->next;
                    (*bcount)++;
                } else {
                    return DIR_NEXT_END;
                }
            } else {
                if ((*b)->next && (*b)->next->next) {
                    *b = (*b)->next->next;
                    (*bcount)++;
                } else {
                    return DIR_NEXT_END;
                }
            }
        } else {
            if ((*b)->next) {
                *b = (*b)->next;
                (*bcount)++;
            } else {
                return DIR_NEXT_END;
            }

            if (step == 1) {
                if ((*a)->next) {
                    *a = (*a)->next;
                } else {
                    return DIR_NEXT_END;
                }
            } else {
                if ((*a)->next && (*a)->next->next) {
                    *a = (*a)->next->next;
                } else {
                    return DIR_NEXT_END;
                }
            }
        }
        return DIR_NEXT;
    } else {
        if (frr >= 1.0) {
            if ((*a)->prev) {
                *a = (*a)->prev;
            } else {
                return DIR_PREV_END;
            }

            if (step == 1) {
                if ((*b)->prev) {
                    *b = (*b)->prev;
                    (*bcount)++;
                } else {
                    return DIR_PREV_END;
                }
            } else {
                if ((*b)->prev && (*b)->prev->prev) {
                    *b = (*b)->prev->prev;
                    (*bcount)++;
                } else {
                    return DIR_PREV_END;
                }
            }
        } else {
            if ((*b)->prev) {
                *b = (*b)->prev;
                (*bcount)++;
            } else {
                return DIR_PREV_END;
            }

            if (step == 1) {
                if ((*a)->prev) {
                    *a = (*a)->prev;
                } else {
                    return DIR_PREV_END;
                }
            } else {
                if ((*a)->prev && (*a)->prev->prev) {
                    *a = (*a)->prev->prev;
                } else {
                    return DIR_PREV_END;
                }
            }
        }
        return DIR_PREV;
    }
}