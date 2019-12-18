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
 scalar_t__ ISSPACE (char) ; 
 int /*<<< orphan*/  parse_arm_disassembler_option (char*) ; 

__attribute__((used)) static void
parse_disassembler_options (char *options)
{
  if (options == NULL)
    return;

  while (*options)
    {
      parse_arm_disassembler_option (options);

      /* Skip forward to next seperator.  */
      while ((*options) && (! ISSPACE (*options)) && (*options != ','))
	++ options;
      /* Skip forward past seperators.  */
      while (ISSPACE (*options) || (*options == ','))
	++ options;      
    }
}