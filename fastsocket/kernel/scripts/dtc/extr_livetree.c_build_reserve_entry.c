#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct TYPE_2__ {void* size; void* address; } ;
struct reserve_info {char* label; int /*<<< orphan*/ * next; TYPE_1__ re; } ;

/* Variables and functions */
 struct reserve_info* xmalloc (int) ; 

struct reserve_info *build_reserve_entry(uint64_t address, uint64_t size,
					 char *label)
{
	struct reserve_info *new = xmalloc(sizeof(*new));

	new->re.address = address;
	new->re.size = size;

	new->next = NULL;

	new->label = label;

	return new;
}