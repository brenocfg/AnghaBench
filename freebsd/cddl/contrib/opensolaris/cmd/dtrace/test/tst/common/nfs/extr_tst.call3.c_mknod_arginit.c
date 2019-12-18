#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  fhandle3_val; int /*<<< orphan*/  fhandle3_len; } ;
struct TYPE_7__ {int /*<<< orphan*/  data_val; int /*<<< orphan*/  data_len; } ;
struct TYPE_8__ {TYPE_1__ data; } ;
struct TYPE_9__ {char* name; TYPE_2__ dir; } ;
struct TYPE_10__ {TYPE_3__ where; } ;
typedef  TYPE_4__ MKNOD3args ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_4__*,int) ; 
 TYPE_5__* rootfh ; 

__attribute__((used)) static void
mknod_arginit(void *argp)
{
	MKNOD3args *args = argp;

	bzero(args, sizeof (*args));
	args->where.dir.data.data_len = rootfh->fhandle3_len;
	args->where.dir.data.data_val = rootfh->fhandle3_val;
	args->where.name = "pookie";
}