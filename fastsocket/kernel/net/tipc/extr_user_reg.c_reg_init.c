#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_3__ {size_t next; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t MAX_USERID ; 
 int /*<<< orphan*/  USER_LIST_SIZE ; 
 TYPE_1__* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t next_free_user ; 
 int /*<<< orphan*/  reg_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 TYPE_1__* users ; 

__attribute__((used)) static int reg_init(void)
{
	u32 i;

	spin_lock_bh(&reg_lock);
	if (!users) {
		users = kzalloc(USER_LIST_SIZE, GFP_ATOMIC);
		if (users) {
			for (i = 1; i <= MAX_USERID; i++) {
				users[i].next = i - 1;
			}
			next_free_user = MAX_USERID;
		}
	}
	spin_unlock_bh(&reg_lock);
	return users ? 0 : -ENOMEM;
}