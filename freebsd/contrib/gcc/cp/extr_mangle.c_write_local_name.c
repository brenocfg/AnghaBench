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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  MANGLE_TRACE_TREE (char*,int /*<<< orphan*/  const) ; 
 scalar_t__ STRING_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  discriminator_for_local_entity (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  discriminator_for_string_literal (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_discriminator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_encoding (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  write_name (int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static void
write_local_name (const tree function, const tree local_entity,
		  const tree entity)
{
  MANGLE_TRACE_TREE ("local-name", entity);

  write_char ('Z');
  write_encoding (function);
  write_char ('E');
  if (TREE_CODE (entity) == STRING_CST)
    {
      write_char ('s');
      write_discriminator (discriminator_for_string_literal (function,
							     entity));
    }
  else
    {
      /* Now the <entity name>.  Let write_name know its being called
	 from <local-name>, so it doesn't try to process the enclosing
	 function scope again.  */
      write_name (entity, /*ignore_local_scope=*/1);
      write_discriminator (discriminator_for_local_entity (local_entity));
    }
}