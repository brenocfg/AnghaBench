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
 int /*<<< orphan*/  d_check_char (struct d_info*,char) ; 
 struct demangle_component** d_cv_qualifiers (struct d_info*,struct demangle_component**,int) ; 
 struct demangle_component* d_prefix (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_nested_name (struct d_info *di)
{
  struct demangle_component *ret;
  struct demangle_component **pret;

  if (! d_check_char (di, 'N'))
    return NULL;

  pret = d_cv_qualifiers (di, &ret, 1);
  if (pret == NULL)
    return NULL;

  *pret = d_prefix (di);
  if (*pret == NULL)
    return NULL;

  if (! d_check_char (di, 'E'))
    return NULL;

  return ret;
}