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
typedef  scalar_t__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  IDENTIFIER_LENGTH (scalar_t__) ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (scalar_t__) ; 
 scalar_t__ IDENTIFIER_TEMPLATE (scalar_t__) ; 
 int /*<<< orphan*/  MANGLE_TRACE_TREE (char*,scalar_t__) ; 
 int /*<<< orphan*/  write_identifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_unsigned_number (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_source_name (tree identifier)
{
  MANGLE_TRACE_TREE ("source-name", identifier);

  /* Never write the whole template-id name including the template
     arguments; we only want the template name.  */
  if (IDENTIFIER_TEMPLATE (identifier))
    identifier = IDENTIFIER_TEMPLATE (identifier);

  write_unsigned_number (IDENTIFIER_LENGTH (identifier));
  write_identifier (IDENTIFIER_POINTER (identifier));
}