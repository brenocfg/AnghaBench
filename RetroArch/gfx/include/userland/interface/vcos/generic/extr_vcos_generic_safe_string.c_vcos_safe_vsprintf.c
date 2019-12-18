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
 scalar_t__ vcos_vsnprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 

size_t vcos_safe_vsprintf(char *buf, size_t buflen, size_t offset, const char *fmt, va_list ap)
{
   size_t space = (offset < buflen) ? (buflen - offset) : 0;

   offset += vcos_vsnprintf(buf ? (buf + offset) : NULL, space, fmt, ap);

   return offset;
}