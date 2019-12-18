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
 int dprintf_formatf (char**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storebuffer ; 

int curl_mvsprintf(char *buffer, const char *format, va_list ap_save)
{
  int retcode;
  retcode = dprintf_formatf(&buffer, storebuffer, format, ap_save);
  *buffer = 0; /* we terminate this with a zero byte */
  return retcode;
}