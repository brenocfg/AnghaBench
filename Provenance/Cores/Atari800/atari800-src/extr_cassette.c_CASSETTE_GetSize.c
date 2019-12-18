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
 unsigned int IMG_TAPE_GetSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cassette_file ; 

unsigned int CASSETTE_GetSize(void)
{
	if (cassette_file == NULL)
		return 0;
	return IMG_TAPE_GetSize(cassette_file);
}