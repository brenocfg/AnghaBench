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
struct TYPE_4__ {int /*<<< orphan*/  m_end; } ;
typedef  TYPE_1__ atf_list_t ;
typedef  int /*<<< orphan*/  atf_list_iter_t ;

/* Variables and functions */
 int /*<<< orphan*/  entry_to_iter (TYPE_1__*,int /*<<< orphan*/ ) ; 

atf_list_iter_t
atf_list_end(atf_list_t *l)
{
    return entry_to_iter(l, l->m_end);
}