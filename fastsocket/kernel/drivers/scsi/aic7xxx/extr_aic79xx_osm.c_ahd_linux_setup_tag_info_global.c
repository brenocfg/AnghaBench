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
struct TYPE_3__ {int* tag_commands; } ;

/* Variables and functions */
 int AHD_NUM_TARGETS ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* aic79xx_tag_info ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahd_linux_setup_tag_info_global(char *p)
{
	int tags, i, j;

	tags = simple_strtoul(p + 1, NULL, 0) & 0xff;
	printf("Setting Global Tags= %d\n", tags);

	for (i = 0; i < ARRAY_SIZE(aic79xx_tag_info); i++) {
		for (j = 0; j < AHD_NUM_TARGETS; j++) {
			aic79xx_tag_info[i].tag_commands[j] = tags;
		}
	}
}