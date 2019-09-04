#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Z; } ;
typedef  TYPE_1__ LoadState ;

/* Variables and functions */
 int /*<<< orphan*/  error (TYPE_1__*,char*) ; 
 scalar_t__ luaZ_read (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static void LoadBlock(LoadState* S, void* b, size_t size)
{
 if (luaZ_read(S->Z,b,size)!=0) error(S,"truncated");
}