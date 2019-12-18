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
typedef  int /*<<< orphan*/  atf_list_citer_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int) ; 
 int /*<<< orphan*/  atf_equal_list_citer_list_citer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_list_begin_c (int /*<<< orphan*/  const*) ; 
 void const* atf_list_citer_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_list_citer_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_list_end_c (int /*<<< orphan*/  const*) ; 
 size_t const atf_list_size (int /*<<< orphan*/  const*) ; 

const void *
atf_list_index_c(const atf_list_t *list, const size_t idx)
{
    atf_list_citer_t iter;

    PRE(idx < atf_list_size(list));

    iter = atf_list_begin_c(list);
    {
        size_t pos = 0;
        while (pos < idx &&
               !atf_equal_list_citer_list_citer((iter),
                                                atf_list_end_c(list))) {
            iter = atf_list_citer_next(iter);
            pos++;
        }
    }
    return atf_list_citer_data(iter);
}