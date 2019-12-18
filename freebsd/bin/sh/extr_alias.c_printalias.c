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
struct alias {int /*<<< orphan*/  val; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  out1c (char) ; 
 int /*<<< orphan*/  out1fmt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out1qstr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
printalias(const struct alias *a)
{
	out1fmt("%s=", a->name);
	out1qstr(a->val);
	out1c('\n');
}