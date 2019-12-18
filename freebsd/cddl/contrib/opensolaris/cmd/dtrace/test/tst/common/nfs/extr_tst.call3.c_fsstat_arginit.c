#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  fhandle3_val; int /*<<< orphan*/  fhandle3_len; } ;
struct TYPE_5__ {int /*<<< orphan*/  data_val; int /*<<< orphan*/  data_len; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
struct TYPE_7__ {TYPE_2__ fsroot; } ;
typedef  TYPE_3__ FSSTAT3args ;

/* Variables and functions */
 TYPE_4__* rootfh ; 

__attribute__((used)) static void
fsstat_arginit(void *argp)
{
	FSSTAT3args *args = argp;

	args->fsroot.data.data_len = rootfh->fhandle3_len;
	args->fsroot.data.data_val = rootfh->fhandle3_val;
}