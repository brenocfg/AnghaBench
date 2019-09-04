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
typedef  int /*<<< orphan*/  zbar_error_t ;
typedef  int /*<<< orphan*/  errsev_t ;
struct TYPE_3__ {scalar_t__ magic; char const* func; char const* detail; int /*<<< orphan*/  type; int /*<<< orphan*/  sev; } ;
typedef  TYPE_1__ errinfo_t ;

/* Variables and functions */
 scalar_t__ ERRINFO_MAGIC ; 
 int /*<<< orphan*/  _zbar_error_spew (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int _zbar_verbosity ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline int err_capture (const void *container,
                               errsev_t sev,
                               zbar_error_t type,
                               const char *func,
                               const char *detail)
{
    errinfo_t *err = (errinfo_t*)container;
    assert(err->magic == ERRINFO_MAGIC);
#ifdef HAVE_ERRNO_H
    if(type == ZBAR_ERR_SYSTEM)
        err->errnum = errno;
#endif
#ifdef _WIN32
    if(type == ZBAR_ERR_WINAPI)
        err->errnum = GetLastError();
#endif
    err->sev = sev;
    err->type = type;
    err->func = func;
    err->detail = detail;
    if(_zbar_verbosity >= 1)
        _zbar_error_spew(err, 0);
    return(-1);
}