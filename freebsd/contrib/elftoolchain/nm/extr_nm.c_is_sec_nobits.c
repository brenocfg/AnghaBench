#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ sh_type; } ;
typedef  TYPE_1__ GElf_Shdr ;

/* Variables and functions */
 scalar_t__ SHT_NOBITS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
is_sec_nobits(GElf_Shdr *s)
{

	assert(s != NULL && "shdr is NULL");

	return (s->sh_type == SHT_NOBITS);
}