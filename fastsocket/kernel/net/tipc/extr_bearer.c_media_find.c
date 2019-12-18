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
typedef  scalar_t__ u32 ;
struct media {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ media_count ; 
 struct media* media_list ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct media *media_find(const char *name)
{
	struct media *m_ptr;
	u32 i;

	for (i = 0, m_ptr = media_list; i < media_count; i++, m_ptr++) {
		if (!strcmp(m_ptr->name, name))
			return m_ptr;
	}
	return NULL;
}