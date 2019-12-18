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
 char const* ggc_alloc_string (char const*,int) ; 
 char* i386_pe_strip_name_encoding (char const*) ; 
 char* strchr (char const*,char) ; 

const char *
i386_pe_strip_name_encoding_full (const char *str)
{
  const char *p;
  const char *name = i386_pe_strip_name_encoding (str);

  /* Strip leading '@' on fastcall symbols.  */
  if (*name == '@')
    name++;

  /* Strip trailing "@n".  */
  p = strchr (name, '@');
  if (p)
    return ggc_alloc_string (name, p - name);

  return name;
}