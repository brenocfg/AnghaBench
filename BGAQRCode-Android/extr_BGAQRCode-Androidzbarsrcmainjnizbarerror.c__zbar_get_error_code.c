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
struct TYPE_2__ {scalar_t__ magic; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ errinfo_t ;

/* Variables and functions */
 scalar_t__ ERRINFO_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 

zbar_error_t _zbar_get_error_code (const void *container)
{
    const errinfo_t *err = container;
    assert(err->magic == ERRINFO_MAGIC);
    return(err->type);
}