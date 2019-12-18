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
struct TYPE_3__ {unsigned int line; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ expanded_location ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_SOURCE_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 unsigned int coverage_checksum_string (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 TYPE_1__ expand_location (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
compute_checksum (void)
{
  expanded_location xloc
    = expand_location (DECL_SOURCE_LOCATION (current_function_decl));
  unsigned chksum = xloc.line;

  chksum = coverage_checksum_string (chksum, xloc.file);
  chksum = coverage_checksum_string
    (chksum, IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (current_function_decl)));

  return chksum;
}