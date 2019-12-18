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
 size_t Curl_strnlen (char const*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static const char *tftp_option_get(const char *buf, size_t len,
                                   const char **option, const char **value)
{
  size_t loc;

  loc = Curl_strnlen(buf, len);
  loc++; /* NULL term */

  if(loc >= len)
    return NULL;
  *option = buf;

  loc += Curl_strnlen(buf + loc, len-loc);
  loc++; /* NULL term */

  if(loc > len)
    return NULL;
  *value = &buf[strlen(*option) + 1];

  return &buf[loc];
}