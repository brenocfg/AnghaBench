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
 scalar_t__ IS_ERR (char*) ; 
 int PTR_ERR (char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 

__attribute__((used)) static int xs_error(char *reply)
{
	if (IS_ERR(reply))
		return PTR_ERR(reply);
	kfree(reply);
	return 0;
}