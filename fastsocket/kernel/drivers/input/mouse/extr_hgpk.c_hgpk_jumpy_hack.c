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
struct psmouse {struct hgpk_data* private; } ;
struct hgpk_data {int /*<<< orphan*/  recalib_wq; } ;

/* Variables and functions */
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  hgpk_err (struct psmouse*,char*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  jumpy_delay ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_queue_work (struct psmouse*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ recalib_delta ; 

__attribute__((used)) static void hgpk_jumpy_hack(struct psmouse *psmouse, int x, int y)
{
	struct hgpk_data *priv = psmouse->private;

	if (abs(x) > recalib_delta || abs(y) > recalib_delta) {
		hgpk_err(psmouse, ">%dpx jump detected (%d,%d)\n",
				recalib_delta, x, y);
		/* My car gets forty rods to the hogshead and that's the
		 * way I likes it! */
		psmouse_queue_work(psmouse, &priv->recalib_wq,
				msecs_to_jiffies(jumpy_delay));
	}
}