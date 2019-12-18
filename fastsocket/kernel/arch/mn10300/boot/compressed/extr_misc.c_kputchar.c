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
 int SC01STR_TBF ; 
 int SC0STR ; 
 int SC0TXB ; 
 int SC1STR ; 
 int SC1TXB ; 

__attribute__((used)) static inline void kputchar(unsigned char ch)
{
#ifdef CONFIG_MN10300_UNIT_ASB2305
	while (SC0STR & SC01STR_TBF)
		continue;

	if (ch == 0x0a) {
		SC0TXB = 0x0d;
		while (SC0STR & SC01STR_TBF)
			continue;
	}

	SC0TXB = ch;

#else
	while (SC1STR & SC01STR_TBF)
		continue;

	if (ch == 0x0a) {
		SC1TXB = 0x0d;
		while (SC1STR & SC01STR_TBF)
			continue;
	}

	SC1TXB = ch;

#endif
}