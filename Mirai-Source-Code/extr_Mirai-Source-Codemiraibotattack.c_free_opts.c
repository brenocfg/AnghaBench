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
struct attack_option {struct attack_option* val; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct attack_option*) ; 

__attribute__((used)) static void free_opts(struct attack_option *opts, int len)
{
    int i;

    if (opts == NULL)
        return;

    for (i = 0; i < len; i++)
    {
        if (opts[i].val != NULL)
            free(opts[i].val);
    }
    free(opts);
}