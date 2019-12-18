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
struct d_info {int /*<<< orphan*/  did_subs; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_check_char (struct d_info*,char) ; 
 struct demangle_component* d_make_template_param (struct d_info*,long) ; 
 long d_number (struct d_info*) ; 
 char d_peek_char (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_template_param (struct d_info *di)
{
  long param;

  if (! d_check_char (di, 'T'))
    return NULL;

  if (d_peek_char (di) == '_')
    param = 0;
  else
    {
      param = d_number (di);
      if (param < 0)
	return NULL;
      param += 1;
    }

  if (! d_check_char (di, '_'))
    return NULL;

  ++di->did_subs;

  return d_make_template_param (di, param);
}