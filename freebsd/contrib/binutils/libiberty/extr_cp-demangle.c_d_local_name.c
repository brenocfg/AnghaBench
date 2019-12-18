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
 int /*<<< orphan*/  DEMANGLE_COMPONENT_LOCAL_NAME ; 
 int /*<<< orphan*/  d_advance (struct d_info*,int) ; 
 int /*<<< orphan*/  d_check_char (struct d_info*,char) ; 
 int /*<<< orphan*/  d_discriminator (struct d_info*) ; 
 struct demangle_component* d_encoding (struct d_info*,int /*<<< orphan*/ ) ; 
 struct demangle_component* d_make_comp (struct d_info*,int /*<<< orphan*/ ,struct demangle_component*,struct demangle_component*) ; 
 struct demangle_component* d_make_name (struct d_info*,char*,int) ; 
 struct demangle_component* d_name (struct d_info*) ; 
 char d_peek_char (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_local_name (struct d_info *di)
{
  struct demangle_component *function;

  if (! d_check_char (di, 'Z'))
    return NULL;

  function = d_encoding (di, 0);

  if (! d_check_char (di, 'E'))
    return NULL;

  if (d_peek_char (di) == 's')
    {
      d_advance (di, 1);
      if (! d_discriminator (di))
	return NULL;
      return d_make_comp (di, DEMANGLE_COMPONENT_LOCAL_NAME, function,
			  d_make_name (di, "string literal",
				       sizeof "string literal" - 1));
    }
  else
    {
      struct demangle_component *name;

      name = d_name (di);
      if (! d_discriminator (di))
	return NULL;
      return d_make_comp (di, DEMANGLE_COMPONENT_LOCAL_NAME, function, name);
    }
}