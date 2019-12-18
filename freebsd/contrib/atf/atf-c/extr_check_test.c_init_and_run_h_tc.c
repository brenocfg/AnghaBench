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
typedef  int /*<<< orphan*/  atf_tc_pack_t ;

/* Variables and functions */
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tc_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_tc_init_pack (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const* const*) ; 
 int /*<<< orphan*/  run_h_tc (int /*<<< orphan*/ *,char const*,char const*,char*) ; 

__attribute__((used)) static
void
init_and_run_h_tc(atf_tc_t *tc, const atf_tc_pack_t *tcpack,
                  const char *outname, const char *errname)
{
    const char *const config[] = { NULL };

    RE(atf_tc_init_pack(tc, tcpack, config));
    run_h_tc(tc, outname, errname, "result");
    atf_tc_fini(tc);
}