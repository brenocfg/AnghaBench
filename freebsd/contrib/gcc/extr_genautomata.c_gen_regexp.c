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
typedef  int /*<<< orphan*/  regexp_t ;

/* Variables and functions */
 int /*<<< orphan*/  gen_regexp_sequence (char const*) ; 
 char const* reserv_str ; 

__attribute__((used)) static regexp_t
gen_regexp (const char *str)
{
  reserv_str = str;
  return gen_regexp_sequence (str);;
}