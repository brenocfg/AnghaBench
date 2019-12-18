#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  fhandle3_val; int /*<<< orphan*/  fhandle3_len; } ;
struct TYPE_9__ {int /*<<< orphan*/  data_val; int /*<<< orphan*/  data_len; } ;
struct TYPE_10__ {TYPE_1__ data; } ;
struct TYPE_11__ {char* name; TYPE_2__ dir; } ;
struct TYPE_12__ {int /*<<< orphan*/  data_val; int /*<<< orphan*/  data_len; } ;
struct TYPE_14__ {TYPE_4__ data; } ;
struct TYPE_13__ {char* name; TYPE_6__ dir; } ;
struct TYPE_15__ {TYPE_3__ to; TYPE_5__ from; } ;
typedef  TYPE_7__ RENAME3args ;

/* Variables and functions */
 TYPE_8__* rootfh ; 

__attribute__((used)) static void
rename_arginit(void *argp)
{
	RENAME3args *args = argp;

	args->from.dir.data.data_len = rootfh->fhandle3_len;
	args->from.dir.data.data_val = rootfh->fhandle3_val;
	args->from.name = "walter";
	args->to.dir.data.data_len = rootfh->fhandle3_len;
	args->to.dir.data.data_val = rootfh->fhandle3_val;
	args->to.name = "wendy";
}