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
typedef  enum tok { ____Placeholder_tok } tok ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int saved_token ; 

__attribute__((used)) static void
pushback(enum tok tok)
{

	if (saved_token != -1)
		abort();
	saved_token = tok;
}