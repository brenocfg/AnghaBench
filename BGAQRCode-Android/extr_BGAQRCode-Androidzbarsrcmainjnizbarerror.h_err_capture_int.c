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
typedef  int /*<<< orphan*/  zbar_error_t ;
typedef  int /*<<< orphan*/  errsev_t ;
struct TYPE_2__ {scalar_t__ magic; int arg_int; } ;
typedef  TYPE_1__ errinfo_t ;

/* Variables and functions */
 scalar_t__ ERRINFO_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int err_capture (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static inline int err_capture_int (const void *container,
                                   errsev_t sev,
                                   zbar_error_t type,
                                   const char *func,
                                   const char *detail,
                                   int arg)
{
    errinfo_t *err = (errinfo_t*)container;
    assert(err->magic == ERRINFO_MAGIC);
    err->arg_int = arg;
    return(err_capture(container, sev, type, func, detail));
}