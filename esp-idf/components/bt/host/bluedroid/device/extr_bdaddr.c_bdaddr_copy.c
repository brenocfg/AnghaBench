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
typedef  int /*<<< orphan*/  bt_bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

bt_bdaddr_t *bdaddr_copy(bt_bdaddr_t *dest, const bt_bdaddr_t *src)
{
    assert(dest != NULL);
    assert(src != NULL);

    return (bt_bdaddr_t *)memcpy(dest, src, sizeof(bt_bdaddr_t));
}