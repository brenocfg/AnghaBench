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
typedef  int /*<<< orphan*/  CGEN_CPU_DESC ;

/* Variables and functions */
 char const* parse_lo16 (int /*<<< orphan*/ ,char const**,int,long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
parse_unsigned16 (CGEN_CPU_DESC cd,
		  const char **strp,
		  int opindex,
		  unsigned long *valuep)
{
  return parse_lo16 (cd, strp, opindex, (long *) valuep, 0);
}