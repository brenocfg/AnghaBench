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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/  perror_fatal (char const*) ; 

__attribute__((used)) static FILE *
ck_fopen (char const *fname, char const *type)
{
  FILE *r = fopen (fname, type);
  if (! r)
    perror_fatal (fname);
  return r;
}