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
 int /*<<< orphan*/  __sc1200wdt_write_data (unsigned char,unsigned char) ; 
 int /*<<< orphan*/  sc1200wdt_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void sc1200wdt_write_data(unsigned char index,
						unsigned char data)
{
	spin_lock(&sc1200wdt_lock);
	__sc1200wdt_write_data(index, data);
	spin_unlock(&sc1200wdt_lock);
}