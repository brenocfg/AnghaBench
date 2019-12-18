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
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stli_flushchars (struct tty_struct*) ; 
 unsigned char* stli_txcookbuf ; 
 int /*<<< orphan*/  stli_txcooksize ; 
 struct tty_struct* stli_txcooktty ; 

__attribute__((used)) static int stli_putchar(struct tty_struct *tty, unsigned char ch)
{
	if (tty != stli_txcooktty) {
		if (stli_txcooktty != NULL)
			stli_flushchars(stli_txcooktty);
		stli_txcooktty = tty;
	}

	stli_txcookbuf[stli_txcooksize++] = ch;
	return 0;
}