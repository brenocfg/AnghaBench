#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  output_lock; TYPE_1__* ops; int /*<<< orphan*/  column; int /*<<< orphan*/  canon_column; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* write ) (struct tty_struct*,unsigned char const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  O_OCRNL (struct tty_struct*) ; 
 int /*<<< orphan*/  O_OLCUC (struct tty_struct*) ; 
 int /*<<< orphan*/  O_ONLCR (struct tty_struct*) ; 
 int /*<<< orphan*/  O_ONLRET (struct tty_struct*) ; 
 int /*<<< orphan*/  O_ONOCR (struct tty_struct*) ; 
 int /*<<< orphan*/  is_continuation (unsigned char,struct tty_struct*) ; 
 int /*<<< orphan*/  iscntrl (unsigned char) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct tty_struct*,unsigned char const*,int) ; 
 int tty_write_room (struct tty_struct*) ; 

__attribute__((used)) static ssize_t process_output_block(struct tty_struct *tty,
				    const unsigned char *buf, unsigned int nr)
{
	int	space;
	int 	i;
	const unsigned char *cp;

	mutex_lock(&tty->output_lock);

	space = tty_write_room(tty);
	if (!space) {
		mutex_unlock(&tty->output_lock);
		return 0;
	}
	if (nr > space)
		nr = space;

	for (i = 0, cp = buf; i < nr; i++, cp++) {
		unsigned char c = *cp;

		switch (c) {
		case '\n':
			if (O_ONLRET(tty))
				tty->column = 0;
			if (O_ONLCR(tty))
				goto break_out;
			tty->canon_column = tty->column;
			break;
		case '\r':
			if (O_ONOCR(tty) && tty->column == 0)
				goto break_out;
			if (O_OCRNL(tty))
				goto break_out;
			tty->canon_column = tty->column = 0;
			break;
		case '\t':
			goto break_out;
		case '\b':
			if (tty->column > 0)
				tty->column--;
			break;
		default:
			if (!iscntrl(c)) {
				if (O_OLCUC(tty))
					goto break_out;
				if (!is_continuation(c, tty))
					tty->column++;
			}
			break;
		}
	}
break_out:
	i = tty->ops->write(tty, buf, i);

	mutex_unlock(&tty->output_lock);
	return i;
}