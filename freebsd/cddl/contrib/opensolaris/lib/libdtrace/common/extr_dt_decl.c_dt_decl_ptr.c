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
typedef  int /*<<< orphan*/  dt_decl_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_K_POINTER ; 
 int /*<<< orphan*/  dt_decl_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dt_decl_push (int /*<<< orphan*/ ) ; 

dt_decl_t *
dt_decl_ptr(void)
{
	return (dt_decl_push(dt_decl_alloc(CTF_K_POINTER, NULL)));
}