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
typedef  int /*<<< orphan*/  buf_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  buf_create_shadow_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,void (*) (int /*<<< orphan*/ ,void*),void*,int) ; 

buf_t
buf_create_shadow_priv(buf_t bp, boolean_t force_copy, uintptr_t external_storage, void (*iodone)(buf_t, void *), void *arg)
{
	return (buf_create_shadow_internal(bp, force_copy, external_storage, iodone, arg, 1));
}