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
struct charset {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ebcdic_print_literally ; 
 int /*<<< orphan*/  ebcdic_to_control ; 
 struct charset* simple_charset (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct charset *
ebcdic_family_charset (const char *name)
{
  return simple_charset (name, 0,
                         ebcdic_print_literally, 0,
                         ebcdic_to_control, 0);
}