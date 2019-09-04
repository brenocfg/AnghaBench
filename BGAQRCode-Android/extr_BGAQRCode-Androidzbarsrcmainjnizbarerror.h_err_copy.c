#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ magic; int /*<<< orphan*/  arg_int; int /*<<< orphan*/ * arg_str; int /*<<< orphan*/  detail; int /*<<< orphan*/  func; int /*<<< orphan*/  type; int /*<<< orphan*/  sev; int /*<<< orphan*/  errnum; } ;
typedef  TYPE_1__ errinfo_t ;

/* Variables and functions */
 scalar_t__ ERRINFO_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline int err_copy (void *dst_c,
                            void *src_c)
{
    errinfo_t *dst = dst_c;
    errinfo_t *src = src_c;
    assert(dst->magic == ERRINFO_MAGIC);
    assert(src->magic == ERRINFO_MAGIC);

    dst->errnum = src->errnum;
    dst->sev = src->sev;
    dst->type = src->type;
    dst->func = src->func;
    dst->detail = src->detail;
    dst->arg_str = src->arg_str;
    src->arg_str = NULL; /* unused at src, avoid double free */
    dst->arg_int = src->arg_int;
    return(-1);
}