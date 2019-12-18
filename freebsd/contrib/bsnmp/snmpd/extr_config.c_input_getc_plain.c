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
 int EOF ; 
 int input_getc_raw () ; 
 int /*<<< orphan*/  input_ungetc (int) ; 

__attribute__((used)) static int
input_getc_plain(void)
{
	int c;

  again:
	if ((c = input_getc_raw()) == '\\') {
		if ((c = input_getc_raw()) == '\n')
			goto again;
		if (c != EOF)
			input_ungetc(c);
		return ('\\');
	}
	return (c);
}