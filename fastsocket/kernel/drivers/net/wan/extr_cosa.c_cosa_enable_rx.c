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
struct cosa_data {int /*<<< orphan*/  rxbitmap; } ;
struct channel_data {int /*<<< orphan*/  num; struct cosa_data* cosa; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_driver_status (struct cosa_data*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cosa_enable_rx(struct channel_data *chan)
{
	struct cosa_data *cosa = chan->cosa;

	if (!test_and_set_bit(chan->num, &cosa->rxbitmap))
		put_driver_status(cosa);
}