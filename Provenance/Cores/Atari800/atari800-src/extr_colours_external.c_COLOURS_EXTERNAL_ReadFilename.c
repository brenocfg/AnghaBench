#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ COLOURS_EXTERNAL_t ;

/* Variables and functions */
 int COLOURS_EXTERNAL_Read (TYPE_1__*) ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  Util_strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int COLOURS_EXTERNAL_ReadFilename(COLOURS_EXTERNAL_t *colours, char *filename)
{
	Util_strlcpy(colours->filename, filename, FILENAME_MAX);
	return COLOURS_EXTERNAL_Read(colours);
}