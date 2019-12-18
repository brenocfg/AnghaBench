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
 int /*<<< orphan*/  dummy_read ; 
 int /*<<< orphan*/  dummy_write ; 
 int /*<<< orphan*/  q68_create () ; 
 int /*<<< orphan*/  q68_set_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q68_set_readb_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q68_set_readw_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q68_set_writeb_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q68_set_writew_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state ; 

__attribute__((used)) static int m68kq68_init(void)
{
    if (!(state = q68_create())) {
        return -1;
    }
    q68_set_irq(state, 0);
    q68_set_readb_func(state, dummy_read);
    q68_set_readw_func(state, dummy_read);
    q68_set_writeb_func(state, dummy_write);
    q68_set_writew_func(state, dummy_write);

    return 0;
}