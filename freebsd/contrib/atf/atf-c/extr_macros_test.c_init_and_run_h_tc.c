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
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tc_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_tc_init (int /*<<< orphan*/ *,char const*,void (*) (atf_tc_t*),void (*) (atf_tc_t const*),int /*<<< orphan*/ *,char const* const*) ; 
 int /*<<< orphan*/  run_h_tc (int /*<<< orphan*/ *,char*,char*,char*) ; 

__attribute__((used)) static
void
init_and_run_h_tc(const char *name, void (*head)(atf_tc_t *),
                  void (*body)(const atf_tc_t *))
{
    atf_tc_t tc;
    const char *const config[] = { NULL };

    RE(atf_tc_init(&tc, name, head, body, NULL, config));
    run_h_tc(&tc, "output", "error", "result");
    atf_tc_fini(&tc);
}