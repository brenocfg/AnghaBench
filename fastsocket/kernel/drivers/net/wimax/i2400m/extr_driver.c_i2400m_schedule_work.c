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
struct i2400m_work {int /*<<< orphan*/  ws; int /*<<< orphan*/  i2400m; } ;
struct i2400m {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,void (*) (struct work_struct*)) ; 
 int /*<<< orphan*/  i2400m_get (struct i2400m*) ; 
 struct i2400m_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int schedule_work (int /*<<< orphan*/ *) ; 

int i2400m_schedule_work(struct i2400m *i2400m,
			 void (*fn)(struct work_struct *), gfp_t gfp_flags)
{
	int result;
	struct i2400m_work *iw;

	result = -ENOMEM;
	iw = kzalloc(sizeof(*iw), gfp_flags);
	if (iw == NULL)
		goto error_kzalloc;
	iw->i2400m = i2400m_get(i2400m);
	INIT_WORK(&iw->ws, fn);
	result = schedule_work(&iw->ws);
	if (result == 0)
		result = -ENXIO;
error_kzalloc:
	return result;
}