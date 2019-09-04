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
typedef  TYPE_1__* j_common_ptr ;
struct TYPE_5__ {int /*<<< orphan*/  env; scalar_t__ valid; } ;
typedef  TYPE_2__ errenv_t ;
struct TYPE_4__ {scalar_t__ err; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 

void zbar_jpeg_error (j_common_ptr cinfo)
{
    errenv_t *jerr = (errenv_t*)cinfo->err;
    assert(jerr->valid);
    jerr->valid = 0;
    longjmp(jerr->env, 1);
    assert(0);
}