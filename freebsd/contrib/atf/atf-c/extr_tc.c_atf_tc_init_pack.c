#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  atf_tc_t ;
struct TYPE_3__ {int /*<<< orphan*/  m_cleanup; int /*<<< orphan*/  m_body; int /*<<< orphan*/  m_head; int /*<<< orphan*/  m_ident; } ;
typedef  TYPE_1__ atf_tc_pack_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_tc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const* const*) ; 

atf_error_t
atf_tc_init_pack(atf_tc_t *tc, const atf_tc_pack_t *pack,
                 const char *const *config)
{
    return atf_tc_init(tc, pack->m_ident, pack->m_head, pack->m_body,
                       pack->m_cleanup, config);
}