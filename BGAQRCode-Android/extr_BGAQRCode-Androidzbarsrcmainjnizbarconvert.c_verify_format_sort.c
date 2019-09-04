#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ format; } ;

/* Variables and functions */
 TYPE_1__* format_defs ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int num_format_defs ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static inline int verify_format_sort (void)
{
    int i;
    for(i = 0; i < num_format_defs; i++) {
        int j = i * 2 + 1;
        if((j < num_format_defs &&
            format_defs[i].format < format_defs[j].format) ||
           (j + 1 < num_format_defs &&
            format_defs[j + 1].format < format_defs[i].format))
            break;
    }
    if(i == num_format_defs)
        return(0);

    /* spew correct order for fix */
    fprintf(stderr, "ERROR: image format list is not sorted!?\n");

#ifdef DEBUG_CONVERT
    assert(num_format_defs);
    uint32_t sorted[num_format_defs];
    uint32_t ordered[num_format_defs];
    for(i = 0; i < num_format_defs; i++)
        sorted[i] = format_defs[i].format;
    qsort(sorted, num_format_defs, sizeof(uint32_t), intsort);
    for(i = 0; i < num_format_defs; i = i << 1 | 1);
    i = (i - 1) / 2;
    ordered[i] = sorted[0];
    int j, k;
    for(j = 1; j < num_format_defs; j++) {
        k = i * 2 + 2;
        if(k < num_format_defs) {
            i = k;
            for(k = k * 2 + 1; k < num_format_defs; k = k * 2 + 1)
                i = k;
        }
        else {
            for(k = (i - 1) / 2; i != k * 2 + 1; k = (i - 1) / 2) {
                assert(i);
                i = k;
            }
            i = k;
        }
        ordered[i] = sorted[j];
    }
    fprintf(stderr, "correct sort order is:");
    for(i = 0; i < num_format_defs; i++)
        fprintf(stderr, " %4.4s", (char*)&ordered[i]);
    fprintf(stderr, "\n");
#endif
    return(-1);
}