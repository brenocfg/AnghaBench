#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct Port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RIOC_CONFIG ; 
 int RIOParam (struct Port*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int rio_set_real_termios(void *ptr)
{
	return RIOParam((struct Port *) ptr, RIOC_CONFIG, 1, 1);
}