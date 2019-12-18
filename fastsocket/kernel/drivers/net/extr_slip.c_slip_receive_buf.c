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
struct tty_struct {struct slip* disc_data; } ;
struct slip {scalar_t__ magic; int mode; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLF_ERROR ; 
 scalar_t__ SLIP_MAGIC ; 
 int SL_MODE_SLIP6 ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slip_unesc (struct slip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slip_unesc6 (struct slip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void slip_receive_buf(struct tty_struct *tty, const unsigned char *cp,
							char *fp, int count)
{
	struct slip *sl = tty->disc_data;

	if (!sl || sl->magic != SLIP_MAGIC || !netif_running(sl->dev))
		return;

	/* Read the characters out of the buffer */
	while (count--) {
		if (fp && *fp++) {
			if (!test_and_set_bit(SLF_ERROR, &sl->flags))
				sl->rx_errors++;
			cp++;
			continue;
		}
#ifdef CONFIG_SLIP_MODE_SLIP6
		if (sl->mode & SL_MODE_SLIP6)
			slip_unesc6(sl, *cp++);
		else
#endif
			slip_unesc(sl, *cp++);
	}
}