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
 int backslash (char) ; 
 int /*<<< orphan*/  big (int) ; 
 int /*<<< orphan*/  f () ; 
 int /*<<< orphan*/  g () ; 
 int /*<<< orphan*/  h () ; 
 int /*<<< orphan*/  limit () ; 
 int /*<<< orphan*/  printf (char*,char,int) ; 

main()
{
	int i; char *s;

	for (s = "bfnrtvx"; *s; s++)
		printf("%c = 0x%x\n", *s, backslash(*s));
	f();
	g();
	h();
	for (i = 0x1000000; i&0x7000000; i += 0x1000000)
		big(i);
	limit();
	return 0;
}