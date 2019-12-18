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
struct run_h_tc_data {int /*<<< orphan*/  m_resname; int /*<<< orphan*/  m_tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tc_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
run_h_tc_child(void *v)
{
    struct run_h_tc_data *data = (struct run_h_tc_data *)v;

    RE(atf_tc_run(data->m_tc, data->m_resname));
}