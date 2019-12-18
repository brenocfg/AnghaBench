#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ws_row; int /*<<< orphan*/  ws_col; } ;
struct tty_struct {int count; scalar_t__ index; TYPE_1__ winsize; struct tty3270* driver_data; scalar_t__ low_latency; } ;
struct TYPE_8__ {int rows; int /*<<< orphan*/  ascebc; int /*<<< orphan*/  cols; } ;
struct tty3270 {int rcl_max; TYPE_2__ view; TYPE_6__* kbd; struct tty_struct* tty; scalar_t__ read; int /*<<< orphan*/  readlet; int /*<<< orphan*/  timer; int /*<<< orphan*/  rcl_lines; int /*<<< orphan*/  update; int /*<<< orphan*/  lines; int /*<<< orphan*/  inattr; } ;
struct file {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/ * fn_handler; struct tty_struct* tty; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct tty3270*) ; 
 size_t KVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  K_CONS ; 
 int /*<<< orphan*/  K_INCRCONSOLE ; 
 int /*<<< orphan*/  K_SCROLLBACK ; 
 int /*<<< orphan*/  K_SCROLLFORW ; 
 int PTR_ERR (struct tty3270*) ; 
 scalar_t__ RAW3270_FIRSTMINOR ; 
 int /*<<< orphan*/  TF_INPUT ; 
 int /*<<< orphan*/  kbd_ascebc (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3270_activate_view (TYPE_2__*) ; 
 int raw3270_add_view (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  raw3270_del_view (TYPE_2__*) ; 
 scalar_t__ raw3270_find_view (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  raw3270_put_view (TYPE_2__*) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 
 int tty3270_alloc_screen (struct tty3270*) ; 
 struct tty3270* tty3270_alloc_view () ; 
 int /*<<< orphan*/  tty3270_blank_line (struct tty3270*) ; 
 int /*<<< orphan*/  tty3270_create_prompt (struct tty3270*) ; 
 int /*<<< orphan*/  tty3270_create_status (struct tty3270*) ; 
 int /*<<< orphan*/  tty3270_exit_tty ; 
 int /*<<< orphan*/  tty3270_fn ; 
 int /*<<< orphan*/  tty3270_free_view (struct tty3270*) ; 
 scalar_t__ tty3270_max_index ; 
 int /*<<< orphan*/  tty3270_rcl_backward ; 
 scalar_t__ tty3270_read_tasklet ; 
 int /*<<< orphan*/  tty3270_scroll_backward ; 
 int /*<<< orphan*/  tty3270_scroll_forward ; 
 scalar_t__ tty3270_update ; 
 int /*<<< orphan*/  tty3270_update_status (struct tty3270*) ; 

__attribute__((used)) static int
tty3270_open(struct tty_struct *tty, struct file * filp)
{
	struct tty3270 *tp;
	int i, rc;

	if (tty->count > 1)
		return 0;
	/* Check if the tty3270 is already there. */
	tp = (struct tty3270 *)
		raw3270_find_view(&tty3270_fn,
				  tty->index + RAW3270_FIRSTMINOR);
	if (!IS_ERR(tp)) {
		tty->driver_data = tp;
		tty->winsize.ws_row = tp->view.rows - 2;
		tty->winsize.ws_col = tp->view.cols;
		tty->low_latency = 0;
		tp->tty = tty;
		tp->kbd->tty = tty;
		tp->inattr = TF_INPUT;
		return 0;
	}
	if (tty3270_max_index < tty->index + 1)
		tty3270_max_index = tty->index + 1;

	/* Quick exit if there is no device for tty->index. */
	if (PTR_ERR(tp) == -ENODEV)
		return -ENODEV;

	/* Allocate tty3270 structure on first open. */
	tp = tty3270_alloc_view();
	if (IS_ERR(tp))
		return PTR_ERR(tp);

	INIT_LIST_HEAD(&tp->lines);
	INIT_LIST_HEAD(&tp->update);
	INIT_LIST_HEAD(&tp->rcl_lines);
	tp->rcl_max = 20;
	setup_timer(&tp->timer, (void (*)(unsigned long)) tty3270_update,
		    (unsigned long) tp);
	tasklet_init(&tp->readlet, 
		     (void (*)(unsigned long)) tty3270_read_tasklet,
		     (unsigned long) tp->read);

	rc = raw3270_add_view(&tp->view, &tty3270_fn,
			      tty->index + RAW3270_FIRSTMINOR);
	if (rc) {
		tty3270_free_view(tp);
		return rc;
	}

	rc = tty3270_alloc_screen(tp);
	if (rc) {
		raw3270_put_view(&tp->view);
		raw3270_del_view(&tp->view);
		return rc;
	}

	tp->tty = tty;
	tty->low_latency = 0;
	tty->driver_data = tp;
	tty->winsize.ws_row = tp->view.rows - 2;
	tty->winsize.ws_col = tp->view.cols;

	tty3270_create_prompt(tp);
	tty3270_create_status(tp);
	tty3270_update_status(tp);

	/* Create blank line for every line in the tty output area. */
	for (i = 0; i < tp->view.rows - 2; i++)
		tty3270_blank_line(tp);

	tp->kbd->tty = tty;
	tp->kbd->fn_handler[KVAL(K_INCRCONSOLE)] = tty3270_exit_tty;
	tp->kbd->fn_handler[KVAL(K_SCROLLBACK)] = tty3270_scroll_backward;
	tp->kbd->fn_handler[KVAL(K_SCROLLFORW)] = tty3270_scroll_forward;
	tp->kbd->fn_handler[KVAL(K_CONS)] = tty3270_rcl_backward;
	kbd_ascebc(tp->kbd, tp->view.ascebc);

	raw3270_activate_view(&tp->view);
	return 0;
}