#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct tty_struct {int dummy; } ;
struct TYPE_5__ {int tail; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int EMUDIF ; 
 int EMUDOF ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfin_jc_tty ; 
 int /*<<< orphan*/  bfin_jc_tty_mutex ; 
 TYPE_1__ bfin_jc_write_buf ; 
 int bfin_read_DBGSTAT () ; 
 int bfin_read_emudat () ; 
 int /*<<< orphan*/  bfin_write_emudat (int) ; 
 int bfin_write_emudat_chars (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  circ_byte (TYPE_1__*,int) ; 
 int circ_cnt (TYPE_1__*) ; 
 scalar_t__ circ_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_string (struct tty_struct*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static int
bfin_jc_emudat_manager(void *arg)
{
	uint32_t inbound_len = 0, outbound_len = 0;

	while (!kthread_should_stop()) {
		/* no one left to give data to, so sleep */
		if (bfin_jc_tty == NULL && circ_empty(&bfin_jc_write_buf)) {
			pr_debug("waiting for readers\n");
			__set_current_state(TASK_UNINTERRUPTIBLE);
			schedule();
			__set_current_state(TASK_RUNNING);
		}

		/* no data available, so just chill */
		if (!(bfin_read_DBGSTAT() & EMUDIF) && circ_empty(&bfin_jc_write_buf)) {
			pr_debug("waiting for data (in_len = %i) (circ: %i %i)\n",
				inbound_len, bfin_jc_write_buf.tail, bfin_jc_write_buf.head);
			if (inbound_len)
				schedule();
			else
				schedule_timeout_interruptible(HZ);
			continue;
		}

		/* if incoming data is ready, eat it */
		if (bfin_read_DBGSTAT() & EMUDIF) {
			struct tty_struct *tty;
			mutex_lock(&bfin_jc_tty_mutex);
			tty = (struct tty_struct *)bfin_jc_tty;
			if (tty != NULL) {
				uint32_t emudat = bfin_read_emudat();
				if (inbound_len == 0) {
					pr_debug("incoming length: 0x%08x\n", emudat);
					inbound_len = emudat;
				} else {
					size_t num_chars = (4 <= inbound_len ? 4 : inbound_len);
					pr_debug("  incoming data: 0x%08x (pushing %zu)\n", emudat, num_chars);
					inbound_len -= num_chars;
					tty_insert_flip_string(tty, (unsigned char *)&emudat, num_chars);
					tty_flip_buffer_push(tty);
				}
			}
			mutex_unlock(&bfin_jc_tty_mutex);
		}

		/* if outgoing data is ready, post it */
		if (!(bfin_read_DBGSTAT() & EMUDOF) && !circ_empty(&bfin_jc_write_buf)) {
			if (outbound_len == 0) {
				outbound_len = circ_cnt(&bfin_jc_write_buf);
				bfin_write_emudat(outbound_len);
				pr_debug("outgoing length: 0x%08x\n", outbound_len);
			} else {
				struct tty_struct *tty;
				int tail = bfin_jc_write_buf.tail;
				size_t ate = (4 <= outbound_len ? 4 : outbound_len);
				uint32_t emudat =
				bfin_write_emudat_chars(
					circ_byte(&bfin_jc_write_buf, tail + 0),
					circ_byte(&bfin_jc_write_buf, tail + 1),
					circ_byte(&bfin_jc_write_buf, tail + 2),
					circ_byte(&bfin_jc_write_buf, tail + 3)
				);
				bfin_jc_write_buf.tail += ate;
				outbound_len -= ate;
				mutex_lock(&bfin_jc_tty_mutex);
				tty = (struct tty_struct *)bfin_jc_tty;
				if (tty)
					tty_wakeup(tty);
				mutex_unlock(&bfin_jc_tty_mutex);
				pr_debug("  outgoing data: 0x%08x (pushing %zu)\n", emudat, ate);
			}
		}
	}

	__set_current_state(TASK_RUNNING);
	return 0;
}