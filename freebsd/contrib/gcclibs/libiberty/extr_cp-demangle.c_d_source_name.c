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
struct demangle_component {int dummy; } ;
struct d_info {struct demangle_component* last_name; } ;

/* Variables and functions */
 struct demangle_component* d_identifier (struct d_info*,long) ; 
 long d_number (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_source_name (struct d_info *di)
{
  long len;
  struct demangle_component *ret;

  len = d_number (di);
  if (len <= 0)
    return NULL;
  ret = d_identifier (di, len);
  di->last_name = ret;
  return ret;
}