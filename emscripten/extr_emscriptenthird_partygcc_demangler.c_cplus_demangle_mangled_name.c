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
struct d_info {int dummy; } ;

/* Variables and functions */
 struct demangle_component* d_encoding (struct d_info*,int) ; 
 char d_next_char (struct d_info*) ; 

struct demangle_component *
cplus_demangle_mangled_name (struct d_info *di, int top_level)
{
  if (d_next_char (di) != '_')
    return NULL;
  if (d_next_char (di) != 'Z')
    return NULL;
  return d_encoding (di, top_level);
}