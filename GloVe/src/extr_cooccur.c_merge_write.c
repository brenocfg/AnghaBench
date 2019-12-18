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
struct TYPE_5__ {scalar_t__ word1; scalar_t__ word2; scalar_t__ val; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ CRECID ;
typedef  int /*<<< orphan*/  CREC ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 

int merge_write(CRECID new, CRECID *old, FILE *fout) {
    if (new.word1 == old->word1 && new.word2 == old->word2) {
        old->val += new.val;
        return 0; // Indicates duplicate entry
    }
    fwrite(old, sizeof(CREC), 1, fout);
    *old = new;
    return 1; // Actually wrote to file
}