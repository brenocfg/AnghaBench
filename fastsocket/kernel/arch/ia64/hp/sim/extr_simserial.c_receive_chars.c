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
 int /*<<< orphan*/  SSC_GETCHAR ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 int /*<<< orphan*/  handle_sysrq (unsigned char,int /*<<< orphan*/ *) ; 
 unsigned char ia64_ssc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_state () ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 scalar_t__ tty_insert_flip_char (struct tty_struct*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static  void receive_chars(struct tty_struct *tty)
{
	unsigned char ch;
	static unsigned char seen_esc = 0;

	while ( (ch = ia64_ssc(0, 0, 0, 0, SSC_GETCHAR)) ) {
		if ( ch == 27 && seen_esc == 0 ) {
			seen_esc = 1;
			continue;
		} else {
			if ( seen_esc==1 && ch == 'O' ) {
				seen_esc = 2;
				continue;
			} else if ( seen_esc == 2 ) {
				if ( ch == 'P' ) /* F1 */
					show_state();
#ifdef CONFIG_MAGIC_SYSRQ
				if ( ch == 'S' ) { /* F4 */
					do
						ch = ia64_ssc(0, 0, 0, 0,
							      SSC_GETCHAR);
					while (!ch);
					handle_sysrq(ch, NULL);
				}
#endif
				seen_esc = 0;
				continue;
			}
		}
		seen_esc = 0;

		if (tty_insert_flip_char(tty, ch, TTY_NORMAL) == 0)
			break;
	}
	tty_flip_buffer_push(tty);
}