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
struct representation {int n_fragments; int /*<<< orphan*/ * fragments; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free_fragment (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_fragment_list(struct representation *pls)
{
    int i;

    for (i = 0; i < pls->n_fragments; i++) {
        free_fragment(&pls->fragments[i]);
    }
    av_freep(&pls->fragments);
    pls->n_fragments = 0;
}