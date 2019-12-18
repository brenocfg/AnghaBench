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
struct i2400ms {int /*<<< orphan*/  i2400m; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2400m_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline
void i2400ms_init(struct i2400ms *i2400ms)
{
	i2400m_init(&i2400ms->i2400m);
}