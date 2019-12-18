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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  DI_format (int,unsigned short,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DI_format_locked (unsigned short id,
                       int type,
                       char *format,
                       va_list argument_list) {
  DI_format (1, id, type, format, argument_list);
}