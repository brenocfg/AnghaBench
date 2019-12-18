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
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_enum {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct nouveau_enum* nouveau_enum_find (struct nouveau_enum const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ) ; 

const struct nouveau_enum *
nouveau_enum_print(const struct nouveau_enum *en, u32 value)
{
	en = nouveau_enum_find(en, value);
	if (en)
		pr_cont("%s", en->name);
	else
		pr_cont("(unknown enum 0x%08x)", value);
	return en;
}