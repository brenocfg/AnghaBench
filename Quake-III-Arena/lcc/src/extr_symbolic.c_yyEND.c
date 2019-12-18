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
 scalar_t__ html ; 
 scalar_t__ isupper (char const) ; 
 int /*<<< orphan*/  print (char*,...) ; 

__attribute__((used)) static void yyEND(const char *tag) {
	if (html)
		print("</%s>", tag);
	if (isupper(*tag))
		print("\n");
}