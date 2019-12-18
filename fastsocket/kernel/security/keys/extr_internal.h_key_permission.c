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
typedef  int /*<<< orphan*/  key_ref_t ;
typedef  int /*<<< orphan*/  key_perm_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_cred () ; 
 int key_task_permission (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int key_permission(const key_ref_t key_ref, key_perm_t perm)
{
	return key_task_permission(key_ref, current_cred(), perm);
}