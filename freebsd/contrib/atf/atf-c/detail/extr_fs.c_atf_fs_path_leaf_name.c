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
struct TYPE_3__ {int /*<<< orphan*/  m_data; } ;
typedef  TYPE_1__ atf_fs_path_t ;
typedef  int /*<<< orphan*/  atf_error_t ;
typedef  int /*<<< orphan*/  atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  INV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_dynstr_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_dynstr_init_substr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t) ; 
 size_t atf_dynstr_npos ; 
 size_t atf_dynstr_rfind_ch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  atf_equal_dynstr_cstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  basename (int /*<<< orphan*/ ) ; 

atf_error_t
atf_fs_path_leaf_name(const atf_fs_path_t *p, atf_dynstr_t *ln)
{
    size_t begpos = atf_dynstr_rfind_ch(&p->m_data, '/');
    atf_error_t err;

    if (begpos == atf_dynstr_npos)
        begpos = 0;
    else
        begpos++;

    err = atf_dynstr_init_substr(ln, &p->m_data, begpos, atf_dynstr_npos);

#if defined(HAVE_CONST_BASENAME)
    INV(atf_equal_dynstr_cstring(ln,
                                 basename(atf_dynstr_cstring(&p->m_data))));
#endif /* defined(HAVE_CONST_BASENAME) */

    return err;
}