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
typedef  scalar_t__ unzFile ;
struct TYPE_2__ {int /*<<< orphan*/  total_out; } ;
typedef  TYPE_1__ mz_compat ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNZ_PARAMERROR ; 

int64_t unzTell64(unzFile file)
{
    mz_compat *compat = (mz_compat *)file;
    if (compat == NULL)
        return UNZ_PARAMERROR;
    return (int64_t)compat->total_out;
}