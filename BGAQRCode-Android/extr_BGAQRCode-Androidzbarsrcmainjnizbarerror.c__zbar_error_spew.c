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
struct TYPE_3__ {scalar_t__ magic; int sev; } ;
typedef  TYPE_1__ errinfo_t ;

/* Variables and functions */
 scalar_t__ ERRINFO_MAGIC ; 
 char* _zbar_error_string (TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

int _zbar_error_spew (const void *container,
                      int verbosity)
{
    const errinfo_t *err = container;
    assert(err->magic == ERRINFO_MAGIC);
    fprintf(stderr, "%s", _zbar_error_string(err, verbosity));
    return(-err->sev);
}