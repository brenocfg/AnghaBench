#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* value; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 char* alloca (int) ; 
 TYPE_1__* configure_default_options ; 
 int /*<<< orphan*/  do_self_spec (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static void
do_option_spec (const char *name, const char *spec)
{
  unsigned int i, value_count, value_len;
  const char *p, *q, *value;
  char *tmp_spec, *tmp_spec_p;

  if (configure_default_options[0].name == NULL)
    return;

  for (i = 0; i < ARRAY_SIZE (configure_default_options); i++)
    if (strcmp (configure_default_options[i].name, name) == 0)
      break;
  if (i == ARRAY_SIZE (configure_default_options))
    return;

  value = configure_default_options[i].value;
  value_len = strlen (value);

  /* Compute the size of the final spec.  */
  value_count = 0;
  p = spec;
  while ((p = strstr (p, "%(VALUE)")) != NULL)
    {
      p ++;
      value_count ++;
    }

  /* Replace each %(VALUE) by the specified value.  */
  tmp_spec = alloca (strlen (spec) + 1
		     + value_count * (value_len - strlen ("%(VALUE)")));
  tmp_spec_p = tmp_spec;
  q = spec;
  while ((p = strstr (q, "%(VALUE)")) != NULL)
    {
      memcpy (tmp_spec_p, q, p - q);
      tmp_spec_p = tmp_spec_p + (p - q);
      memcpy (tmp_spec_p, value, value_len);
      tmp_spec_p += value_len;
      q = p + strlen ("%(VALUE)");
    }
  strcpy (tmp_spec_p, q);

  do_self_spec (tmp_spec);
}