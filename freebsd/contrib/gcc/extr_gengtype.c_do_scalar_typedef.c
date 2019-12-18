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
struct fileloc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_scalar_type (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_typedef (char const*,int /*<<< orphan*/ ,struct fileloc*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
do_scalar_typedef (const char *s, struct fileloc *pos)
{
  do_typedef (s, create_scalar_type (s, strlen (s)), pos);
}