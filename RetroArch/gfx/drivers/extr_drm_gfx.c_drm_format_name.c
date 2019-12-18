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
typedef  int /*<<< orphan*/  format_str ;
struct TYPE_3__ {unsigned int const format; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* format_info ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void drm_format_name(const unsigned int fourcc, char *format_str)
{
	unsigned int i;
	for (i = 0; i < ARRAY_SIZE(format_info); i++)
   {
		if (format_info[i].format == fourcc)
			strlcpy(format_str, format_info[i].name, sizeof(format_str));
	}
}