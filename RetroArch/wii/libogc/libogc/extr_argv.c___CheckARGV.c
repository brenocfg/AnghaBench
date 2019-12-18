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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ argvMagic; char* commandLine; scalar_t__ endARGV; int /*<<< orphan*/  length; int /*<<< orphan*/ * argv; scalar_t__ argc; } ;

/* Variables and functions */
 scalar_t__ ARGV_MAGIC ; 
 scalar_t__ __Arena1Lo ; 
 char* __argvArena1Lo ; 
 TYPE_1__* __system_argv ; 
 int /*<<< orphan*/  build_argv (TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void __CheckARGV() {

	if ( __system_argv->argvMagic != ARGV_MAGIC ) {
		__system_argv->argc = 0;
		__system_argv->argv = NULL;
		return;
	}

	u8 *dest = (u8 *)( ((int)__Arena1Lo + 3) & ~3);

	memmove(dest, __system_argv->commandLine, __system_argv->length);
	__system_argv->commandLine = (char *)dest;
	build_argv(__system_argv);

	__argvArena1Lo = (char *)__system_argv->endARGV;

}