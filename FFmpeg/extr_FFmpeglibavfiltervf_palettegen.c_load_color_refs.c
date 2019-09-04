#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hist_node {int nb_entries; struct color_ref* entries; } ;
struct color_ref {int dummy; } ;

/* Variables and functions */
 int HIST_SIZE ; 
 struct color_ref** av_malloc_array (int,int) ; 

__attribute__((used)) static struct color_ref **load_color_refs(const struct hist_node *hist, int nb_refs)
{
    int i, j, k = 0;
    struct color_ref **refs = av_malloc_array(nb_refs, sizeof(*refs));

    if (!refs)
        return NULL;

    for (j = 0; j < HIST_SIZE; j++) {
        const struct hist_node *node = &hist[j];

        for (i = 0; i < node->nb_entries; i++)
            refs[k++] = &node->entries[i];
    }

    return refs;
}