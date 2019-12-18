#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  fhandle3_val; int /*<<< orphan*/  fhandle3_len; } ;
struct TYPE_8__ {int /*<<< orphan*/  data_val; int /*<<< orphan*/  data_len; } ;
struct TYPE_9__ {TYPE_1__ data; } ;
struct TYPE_10__ {char* name; TYPE_2__ dir; } ;
struct TYPE_11__ {int /*<<< orphan*/  data_val; int /*<<< orphan*/  data_len; } ;
struct TYPE_12__ {TYPE_4__ data; } ;
struct TYPE_13__ {TYPE_3__ link; TYPE_5__ file; } ;
typedef  TYPE_6__ LINK3args ;

/* Variables and functions */
 TYPE_7__* rootfh ; 

__attribute__((used)) static void
link_arginit(void *argp)
{
	LINK3args *args = argp;

	args->file.data.data_len = rootfh->fhandle3_len;
	args->file.data.data_val = rootfh->fhandle3_val;
	args->link.dir.data.data_len = rootfh->fhandle3_len;
	args->link.dir.data.data_val = rootfh->fhandle3_val;
	args->link.name = "samf";
}