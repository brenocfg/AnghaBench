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
struct inet_diag_handler {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  inet_diag_table_mutex ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void inet_diag_unlock_handler(
	const struct inet_diag_handler *handler)
{
	mutex_unlock(&inet_diag_table_mutex);
}