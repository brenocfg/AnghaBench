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
struct TYPE_3__ {int /*<<< orphan*/  (* write ) (TYPE_1__*,char const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* current_device ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void putdbgstr(const char *str)
{
	current_device->write(current_device,str,strlen(str));
}