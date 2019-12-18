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
typedef  int /*<<< orphan*/  msg ;
struct TYPE_2__ {int /*<<< orphan*/  (* fMessage ) (char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_MAX ; 
 TYPE_1__* UI_driver ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,char const*) ; 
 int /*<<< orphan*/  stub1 (char*,int) ; 

__attribute__((used)) static void FilenameMessage(const char *format, const char *filename)
{
	char msg[FILENAME_MAX + 30];
	snprintf(msg, sizeof(msg), format, filename);
	UI_driver->fMessage(msg, 1);
}