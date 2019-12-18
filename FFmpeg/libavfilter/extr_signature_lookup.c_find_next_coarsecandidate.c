#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  int /*<<< orphan*/  SignatureContext ;
typedef  TYPE_1__ CoarseSignature ;

/* Variables and functions */
 scalar_t__ get_jaccarddist (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int find_next_coarsecandidate(SignatureContext *sc, CoarseSignature *secondstart, CoarseSignature **first, CoarseSignature **second, int start)
{
    /* go one coarsesignature foreword */
    if (!start) {
        if ((*second)->next) {
            *second = (*second)->next;
        } else if ((*first)->next) {
            *second = secondstart;
            *first = (*first)->next;
        } else {
            return 0;
        }
    }

    while (1) {
        if (get_jaccarddist(sc, *first, *second))
            return 1;

        /* next signature */
        if ((*second)->next) {
            *second = (*second)->next;
        } else if ((*first)->next) {
            *second = secondstart;
            *first = (*first)->next;
        } else {
            return 0;
        }
    }
}