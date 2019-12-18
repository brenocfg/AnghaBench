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
#define  FEQUAL 129 
#define  FSTAR 128 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static const char *
conf_num(char *b, size_t l, int n)
{
	switch (n) {
	case FSTAR:
		return "*";
	case FEQUAL:
		return "=";
	default:
		snprintf(b, l, "%d", n);
		return b;
	}
}