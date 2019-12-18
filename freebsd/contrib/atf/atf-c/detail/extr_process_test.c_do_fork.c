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
struct child_print_data {char* member_0; } ;
struct base_stream {int /*<<< orphan*/  (* fini ) (void*) ;int /*<<< orphan*/  (* process ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  m_sb_ptr; int /*<<< orphan*/  (* init ) (void*) ;} ;
typedef  int /*<<< orphan*/  atf_process_status_t ;
typedef  int /*<<< orphan*/  atf_process_child_t ;

/* Variables and functions */
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_process_child_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_process_fork (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct child_print_data*) ; 
 int /*<<< orphan*/  atf_process_status_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  child_print ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  stub3 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (void*) ; 
 int /*<<< orphan*/  stub6 (void*) ; 

__attribute__((used)) static
void
do_fork(const struct base_stream *outfs, void *out,
        const struct base_stream *errfs, void *err)
{
    atf_process_child_t child;
    atf_process_status_t status;
    struct child_print_data cpd = { "msg" };

    outfs->init(out);
    errfs->init(err);

    RE(atf_process_fork(&child, child_print, outfs->m_sb_ptr,
                        errfs->m_sb_ptr, &cpd));
    if (outfs->process != NULL)
        outfs->process(out, &child);
    if (errfs->process != NULL)
        errfs->process(err, &child);
    RE(atf_process_child_wait(&child, &status));

    outfs->fini(out);
    errfs->fini(err);

    atf_process_status_fini(&status);
}