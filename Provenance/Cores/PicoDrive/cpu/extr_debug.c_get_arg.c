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
 char const* get_token (char*,int,char const*) ; 

__attribute__((used)) static const char *get_arg(char *buf, int blen, const char *str)
{
  if (*str == ';')
    return NULL;
  return get_token(buf, blen, str);
}