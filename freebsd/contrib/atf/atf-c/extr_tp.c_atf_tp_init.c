#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct atf_tp_impl {int dummy; } ;
struct TYPE_4__ {TYPE_2__* pimpl; } ;
typedef  TYPE_1__ atf_tp_t ;
typedef  int /*<<< orphan*/  atf_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  m_tcs; int /*<<< orphan*/  m_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  INV (int) ; 
 int /*<<< orphan*/  PRE (int /*<<< orphan*/ ) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_list_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_map_init_charpp (int /*<<< orphan*/ *,char const* const*) ; 
 int /*<<< orphan*/  atf_no_memory_error () ; 
 TYPE_2__* malloc (int) ; 

atf_error_t
atf_tp_init(atf_tp_t *tp, const char *const *config)
{
    atf_error_t err;

    PRE(config != NULL);

    tp->pimpl = malloc(sizeof(struct atf_tp_impl));
    if (tp->pimpl == NULL)
        return atf_no_memory_error();

    err = atf_list_init(&tp->pimpl->m_tcs);
    if (atf_is_error(err))
        goto out;

    err = atf_map_init_charpp(&tp->pimpl->m_config, config);
    if (atf_is_error(err)) {
        atf_list_fini(&tp->pimpl->m_tcs);
        goto out;
    }

    INV(!atf_is_error(err));
out:
    return err;
}