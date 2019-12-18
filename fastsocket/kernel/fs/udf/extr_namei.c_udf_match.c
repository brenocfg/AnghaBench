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

/* Variables and functions */
 int /*<<< orphan*/  memcmp (char const*,char const*,int) ; 

__attribute__((used)) static inline int udf_match(int len1, const char *name1, int len2,
			    const char *name2)
{
	if (len1 != len2)
		return 0;

	return !memcmp(name1, name2, len1);
}