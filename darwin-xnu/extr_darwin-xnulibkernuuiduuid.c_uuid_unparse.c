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
typedef  int /*<<< orphan*/  uuid_string_t ;

/* Variables and functions */
 int /*<<< orphan*/  uuid_unparse_upper (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

void
uuid_unparse(const uuid_t uu, uuid_string_t out)
{
	uuid_unparse_upper(uu, out);
}