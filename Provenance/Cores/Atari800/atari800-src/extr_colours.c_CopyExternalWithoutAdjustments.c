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
struct TYPE_2__ {unsigned char* palette; } ;

/* Variables and functions */
 int /*<<< orphan*/  Colours_SetRGB (int,unsigned char,unsigned char,unsigned char,int /*<<< orphan*/ ) ; 
 TYPE_1__* Colours_external ; 
 int /*<<< orphan*/  Colours_table ; 

__attribute__((used)) static void CopyExternalWithoutAdjustments(void)
{
	int i;
	unsigned char *ext_ptr;
	for (i = 0, ext_ptr = Colours_external->palette; i < 256; i ++, ext_ptr += 3)
		Colours_SetRGB(i, *ext_ptr, *(ext_ptr + 1), *(ext_ptr + 2), Colours_table);
}