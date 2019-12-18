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

/* Variables and functions */
 int /*<<< orphan*/  define_config (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ len_config ; 

__attribute__((used)) static void clear_config(void)
{
	len_config = 0;
	define_config("", 0);
}