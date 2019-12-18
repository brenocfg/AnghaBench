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
typedef  enum filebrowser_enums { ____Placeholder_filebrowser_enums } filebrowser_enums ;

/* Variables and functions */
 int filebrowser_types ; 

void filebrowser_set_type(enum filebrowser_enums type)
{
   filebrowser_types = type;
}