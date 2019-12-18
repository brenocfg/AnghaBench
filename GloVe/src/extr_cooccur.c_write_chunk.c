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
struct TYPE_4__ {scalar_t__ word1; scalar_t__ word2; scalar_t__ val; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ CREC ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 

int write_chunk(CREC *cr, long long length, FILE *fout) {
    if (length == 0) return 0;

    long long a = 0;
    CREC old = cr[a];
    
    for (a = 1; a < length; a++) {
        if (cr[a].word1 == old.word1 && cr[a].word2 == old.word2) {
            old.val += cr[a].val;
            continue;
        }
        fwrite(&old, sizeof(CREC), 1, fout);
        old = cr[a];
    }
    fwrite(&old, sizeof(CREC), 1, fout);
    return 0;
}