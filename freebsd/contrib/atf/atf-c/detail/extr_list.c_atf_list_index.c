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
typedef  int /*<<< orphan*/  atf_list_t ;
typedef  int /*<<< orphan*/  atf_list_iter_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int) ; 
 int /*<<< orphan*/  atf_equal_list_iter_list_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_list_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_list_end (int /*<<< orphan*/ *) ; 
 void* atf_list_iter_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_list_iter_next (int /*<<< orphan*/ ) ; 
 size_t const atf_list_size (int /*<<< orphan*/ *) ; 

void *
atf_list_index(atf_list_t *list, const size_t idx)
{
    atf_list_iter_t iter;

    PRE(idx < atf_list_size(list));

    iter = atf_list_begin(list);
    {
        size_t pos = 0;
        while (pos < idx &&
               !atf_equal_list_iter_list_iter((iter), atf_list_end(list))) {
            iter = atf_list_iter_next(iter);
            pos++;
        }
    }
    return atf_list_iter_data(iter);
}