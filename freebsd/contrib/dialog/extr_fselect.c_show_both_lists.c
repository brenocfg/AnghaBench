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
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 char* leaf_of (char*) ; 
 scalar_t__ show_list (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
show_both_lists(char *input, LIST * d_list, LIST * f_list, bool keep)
{
    char *leaf = leaf_of(input);

    return show_list(leaf, d_list, keep) || show_list(leaf, f_list, keep);
}