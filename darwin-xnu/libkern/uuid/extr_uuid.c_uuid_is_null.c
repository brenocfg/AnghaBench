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
typedef  int /*<<< orphan*/  uuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  UUID_NULL ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int) ; 

int
uuid_is_null(const uuid_t uu)
{
	return !memcmp(uu, UUID_NULL, sizeof(uuid_t));
}