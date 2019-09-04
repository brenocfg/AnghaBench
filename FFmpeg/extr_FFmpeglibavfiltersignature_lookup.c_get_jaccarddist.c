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
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {int thworddist; int thcomposdist; } ;
typedef  TYPE_1__ SignatureContext ;
typedef  TYPE_2__ CoarseSignature ;

/* Variables and functions */
 int intersection_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int union_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_jaccarddist(SignatureContext *sc, CoarseSignature *first, CoarseSignature *second)
{
    int jaccarddist, i, composdist = 0, cwthcount = 0;
    for (i = 0; i < 5; i++) {
        if ((jaccarddist = intersection_word(first->data[i], second->data[i])) > 0) {
            jaccarddist /= union_word(first->data[i], second->data[i]);
        }
        if (jaccarddist >= sc->thworddist) {
            if (++cwthcount > 2) {
                /* more than half (5/2) of distances are too wide */
                return 0;
            }
        }
        composdist += jaccarddist;
        if (composdist > sc->thcomposdist) {
            return 0;
        }
    }
    return 1;
}