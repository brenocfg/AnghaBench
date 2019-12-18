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
struct nsprintf {char* buffer; size_t length; size_t max; } ;

/* Variables and functions */
 int /*<<< orphan*/  addbyter ; 
 int dprintf_formatf (struct nsprintf*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int curl_mvsnprintf(char *buffer, size_t maxlength, const char *format,
                    va_list ap_save)
{
  int retcode;
  struct nsprintf info;

  info.buffer = buffer;
  info.length = 0;
  info.max = maxlength;

  retcode = dprintf_formatf(&info, addbyter, format, ap_save);
  if((retcode != -1) && info.max) {
    /* we terminate this with a zero byte */
    if(info.max == info.length)
      /* we're at maximum, scrap the last letter */
      info.buffer[-1] = 0;
    else
      info.buffer[0] = 0;
  }
  return retcode;
}